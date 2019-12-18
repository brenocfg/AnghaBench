#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {unsigned long CPACR; } ;

/* Variables and functions */
 TYPE_1__* SCB ; 
 int _ebss ; 
 int _edata ; 
 int _sbss ; 
 int _sdata ; 
 int _sidata ; 
 int /*<<< orphan*/  isr_vector ; 
 int /*<<< orphan*/  samd_init () ; 
 int /*<<< orphan*/  samd_main () ; 

void Reset_Handler(void) {
    // Set stack pointer
    #if __CORTEX_M >= 0x03
    __asm volatile ("ldr sp, =_estack");
    #else
    __asm volatile ("ldr r0, =_estack");
    __asm volatile ("mov sp, r0");
    #endif
    // Copy .data section from flash to RAM
    for (uint32_t *src = &_sidata, *dest = &_sdata; dest < &_edata;) {
        *dest++ = *src++;
    }
    // Zero out .bss section
    for (uint32_t *dest = &_sbss; dest < &_ebss;) {
        *dest++ = 0;
    }

    // When we get here: stack is initialised, bss is clear, data is copied

    #if __FPU_PRESENT == 1 && __FPU_USED == 1
    // Set CP10 and CP11 Full Access
    SCB->CPACR |= (3UL << 10 * 2) | (3UL << 11 * 2);
    #endif

    // SCB->VTOR
    *((volatile uint32_t*)0xe000ed08) = (uint32_t)&isr_vector;

    // SCB->CCR: enable 8-byte stack alignment for IRQ handlers, in accord with EABI
    *((volatile uint32_t*)0xe000ed14) |= 1 << 9;

    // Initialise the cpu and peripherals
    samd_init();

    // Now that we have a basic system up and running we can call main
    samd_main();

    // we must not return
    for (;;) {
    }
}