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
 int LSR_DR ; 
 int /*<<< orphan*/  REG_LSR ; 
 int lpc_uart_reg_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_uart_rx_empty(void) {
    return !(lpc_uart_reg_read(REG_LSR) & LSR_DR);
}