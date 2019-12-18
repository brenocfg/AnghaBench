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
 int /*<<< orphan*/  REG_RBR ; 
 int /*<<< orphan*/  lpc_uart_reg_write (int /*<<< orphan*/ ,char) ; 
 scalar_t__ lpc_uart_tx_full () ; 

void lpc_uart_write(char c) {
    while (lpc_uart_tx_full());
    lpc_uart_reg_write(REG_RBR, c);
}