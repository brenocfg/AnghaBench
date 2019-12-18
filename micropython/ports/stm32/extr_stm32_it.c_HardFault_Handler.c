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

__attribute__((naked))
void HardFault_Handler(void) {

    // From the ARMv7M Architecture Reference Manual, section B.1.5.6
    // on entry to the Exception, the LR register contains, amongst other
    // things, the value of CONTROL.SPSEL. This can be found in bit 3.
    //
    // If CONTROL.SPSEL is 0, then the exception was stacked up using the
    // main stack pointer (aka MSP). If CONTROL.SPSEL is 1, then the exception
    // was stacked up using the process stack pointer (aka PSP).

    #if __CORTEX_M == 0
    __asm volatile(
    " mov r0, lr    \n"
    " lsr r0, r0, #3 \n"        // Shift Bit 3 into carry to see which stack pointer we should use.
    " mrs r0, msp   \n"         // Make R0 point to main stack pointer
    " bcc .use_msp  \n"         // Keep MSP in R0 if SPSEL (carry) is 0
    " mrs r0, psp   \n"         // Make R0 point to process stack pointer
    " .use_msp:     \n"
    " b HardFault_C_Handler \n" // Off to C land
    );
    #else
    __asm volatile(
    " tst lr, #4    \n"         // Test Bit 3 to see which stack pointer we should use.
    " ite eq        \n"         // Tell the assembler that the nest 2 instructions are if-then-else
    " mrseq r0, msp \n"         // Make R0 point to main stack pointer
    " mrsne r0, psp \n"         // Make R0 point to process stack pointer
    " b HardFault_C_Handler \n" // Off to C land
    );
    #endif
}