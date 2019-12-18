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
typedef  char uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  POTATO_CONSOLE_TX ; 
 int /*<<< orphan*/  potato_uart_reg_write (int /*<<< orphan*/ ,char) ; 
 scalar_t__ potato_uart_tx_full () ; 

void potato_uart_write(char c) {
    uint64_t val;

    val = c;

    while (potato_uart_tx_full());
    potato_uart_reg_write(POTATO_CONSOLE_TX, val);
}