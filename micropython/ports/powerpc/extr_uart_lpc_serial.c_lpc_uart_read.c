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
 int /*<<< orphan*/  REG_THR ; 
 char lpc_uart_reg_read (int /*<<< orphan*/ ) ; 
 scalar_t__ lpc_uart_rx_empty () ; 

char lpc_uart_read(void) {
    while (lpc_uart_rx_empty()) ;
    return lpc_uart_reg_read(REG_THR);
}