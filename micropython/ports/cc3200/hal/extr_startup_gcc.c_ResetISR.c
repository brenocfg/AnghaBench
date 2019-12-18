#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  main () ; 

void ResetISR(void)
{
#if defined(DEBUG) && !defined(BOOTLOADER)
    {
        //
        // Fill the main stack with a known value so that
        // we can measure the main stack high water mark
        //
        __asm volatile
        (
                "ldr     r0, =_stack        \n"
                "ldr     r1, =_estack       \n"
                "mov     r2, #0x55555555    \n"
        ".thumb_func                        \n"
        "fill_loop:                         \n"
                "cmp     r0, r1             \n"
                "it      lt                 \n"
                "strlt   r2, [r0], #4       \n"
                "blt     fill_loop          \n"
        );
    }
#endif

    {
        // Get the initial stack pointer location from the vector table
        // and write this value to the msp register
        __asm volatile
        (
                "ldr r0, =_text             \n"
                "ldr r0, [r0]               \n"
                "msr msp, r0                \n"
        );
    }

    {
        //
        // Zero fill the bss segment.
        //
        __asm volatile
        (
                "ldr     r0, =_bss      \n"
                "ldr     r1, =_ebss     \n"
                "mov     r2, #0         \n"
        ".thumb_func                    \n"
        "zero_loop:                     \n"
                "cmp     r0, r1         \n"
                "it      lt             \n"
                "strlt   r2, [r0], #4   \n"
                "blt     zero_loop      \n"
        );
    }

    {
        //
        // Call the application's entry point.
        //
        main();
    }
}