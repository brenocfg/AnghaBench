#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct uart_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int (* get_ipcr ) (struct uart_port*) ;scalar_t__ (* tx_rdy ) (struct uart_port*) ;int /*<<< orphan*/  (* tx_clr_irq ) (struct uart_port*) ;scalar_t__ (* rx_rdy ) (struct uart_port*) ;int /*<<< orphan*/  (* rx_clr_irq ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long ISR_PASS_LIMIT ; 
 int MPC52xx_PSC_CTS ; 
 int MPC52xx_PSC_DCD ; 
 int MPC52xx_PSC_D_CTS ; 
 int MPC52xx_PSC_D_DCD ; 
 unsigned int mpc52xx_uart_int_rx_chars (struct uart_port*) ; 
 unsigned int mpc52xx_uart_int_tx_chars (struct uart_port*) ; 
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 scalar_t__ stub2 (struct uart_port*) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*) ; 
 scalar_t__ stub4 (struct uart_port*) ; 
 int stub5 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,int) ; 

__attribute__((used)) static irqreturn_t
mpc5xxx_uart_process_int(struct uart_port *port)
{
	unsigned long pass = ISR_PASS_LIMIT;
	unsigned int keepgoing;
	u8 status;

	/* While we have stuff to do, we continue */
	do {
		/* If we don't find anything to do, we stop */
		keepgoing = 0;

		psc_ops->rx_clr_irq(port);
		if (psc_ops->rx_rdy(port))
			keepgoing |= mpc52xx_uart_int_rx_chars(port);

		psc_ops->tx_clr_irq(port);
		if (psc_ops->tx_rdy(port))
			keepgoing |= mpc52xx_uart_int_tx_chars(port);

		status = psc_ops->get_ipcr(port);
		if (status & MPC52xx_PSC_D_DCD)
			uart_handle_dcd_change(port, !(status & MPC52xx_PSC_DCD));

		if (status & MPC52xx_PSC_D_CTS)
			uart_handle_cts_change(port, !(status & MPC52xx_PSC_CTS));

		/* Limit number of iteration */
		if (!(--pass))
			keepgoing = 0;

	} while (keepgoing);

	return IRQ_HANDLED;
}