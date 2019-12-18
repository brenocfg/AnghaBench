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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ potato_uart_base ; 

void potato_uart_reg_write(int offset, uint64_t val) {
    uint64_t addr;

    addr = potato_uart_base + offset;

    *(volatile uint64_t *)addr = val;
}