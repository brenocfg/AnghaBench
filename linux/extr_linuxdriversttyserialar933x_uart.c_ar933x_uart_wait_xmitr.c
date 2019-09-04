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
struct ar933x_uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 unsigned int AR933X_UART_DATA_TX_CSR ; 
 unsigned int ar933x_uart_read (struct ar933x_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar933x_uart_wait_xmitr(struct ar933x_uart_port *up)
{
	unsigned int status;
	unsigned int timeout = 60000;

	/* Wait up to 60ms for the character(s) to be sent. */
	do {
		status = ar933x_uart_read(up, AR933X_UART_DATA_REG);
		if (--timeout == 0)
			break;
		udelay(1);
	} while ((status & AR933X_UART_DATA_TX_CSR) == 0);
}