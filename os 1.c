// kernel.c

#include <stdint.h>
#include "multiboot.h"

// Define stack size and task limit
#define STACK_SIZE 4096
#define NUM_TASKS 2

// Define structure for a task's state
typedef struct {
    uint32_t *stack;  // Stack pointer for the task
} Task;

// Arrays for task states and stacks
Task tasks[NUM_TASKS];
uint32_t stacks[NUM_TASKS][STACK_SIZE];

// Index of the current task
int current_task = 0;

// Function prototypes
void task1();
void task2();
void switch_task();
void init_tasks();

// Entry point of the kernel
void kernel_main(multiboot_info_t *mbd, unsigned int magic) {
    // Initialize the tasks
    init_tasks();

    // Switch to the first task
    while (1) {
        switch_task();
    }
}

// Task 1 function
void task1() {
    while (1) {
        // Perform task 1 operations here
        // For demonstration, we'll just switch tasks
        switch_task();
    }
}

// Task 2 function
void task2() {
    while (1) {
        // Perform task 2 operations here
        // For demonstration, we'll just switch tasks
        switch_task();
    }
}

// Function to initialize tasks
void init_tasks() {
    // Initialize stack and task state for task 1
    tasks[0].stack = &stacks[0][STACK_SIZE - 1];
    *tasks[0].stack = (uint32_t)task1;

    // Initialize stack and task state for task 2
    tasks[1].stack = &stacks[1][STACK_SIZE - 1];
    *tasks[1].stack = (uint32_t)task2;
}

// Function to switch tasks
void switch_task() {
    // Save current task state
    asm volatile("mov %%esp, %0" : "=r" (tasks[current_task].stack));

    // Move to the next task
    current_task = (current_task + 1) % NUM_TASKS;

    // Restore the next task state
    asm volatile("mov %0, %%esp" : : "r" (tasks[current_task].stack));

    // Return to the task
    asm volatile("ret");
}
