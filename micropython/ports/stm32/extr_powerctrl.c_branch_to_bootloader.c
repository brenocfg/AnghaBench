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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static __attribute__((naked)) void branch_to_bootloader(uint32_t r0, uint32_t bl_addr) {
    __asm volatile (
        "ldr r2, [r1, #0]\n"    // get address of stack pointer
        "msr msp, r2\n"         // get stack pointer
        "ldr r2, [r1, #4]\n"    // get address of destination
        "bx r2\n"               // branch to bootloader
    );
}