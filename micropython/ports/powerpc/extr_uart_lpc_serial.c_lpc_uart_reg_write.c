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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ lpc_uart_base ; 

__attribute__((used)) static void lpc_uart_reg_write(uint64_t offset, uint8_t val) {
    uint64_t addr;

    addr = lpc_uart_base + offset;

    *(volatile uint8_t *)addr = val;
}