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
struct uart_port {int dummy; } ;
struct atmel_uart_port {int tx_done_mask; int tx_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int /*<<< orphan*/  ATMEL_PDC_PTSR ; 
 int ATMEL_PDC_TXTEN ; 
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int ATMEL_US_TXEN ; 
 int /*<<< orphan*/  atmel_stop_rx (struct uart_port*) ; 
 scalar_t__ atmel_uart_is_half_duplex (struct uart_port*) ; 
 int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atmel_use_dma_tx (struct uart_port*) ; 
 scalar_t__ atmel_use_pdc_tx (struct uart_port*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_start_tx(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_pdc_tx(port) && (atmel_uart_readl(port, ATMEL_PDC_PTSR)
				       & ATMEL_PDC_TXTEN))
		/* The transmitter is already running.  Yes, we
		   really need this.*/
		return;

	if (atmel_use_pdc_tx(port) || atmel_use_dma_tx(port))
		if (atmel_uart_is_half_duplex(port))
			atmel_stop_rx(port);

	if (atmel_use_pdc_tx(port))
		/* re-enable PDC transmit */
		atmel_uart_writel(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);

	/* Enable interrupts */
	atmel_uart_writel(port, ATMEL_US_IER, atmel_port->tx_done_mask);

	/* re-enable the transmitter */
	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_TXEN);
	atmel_port->tx_stopped = false;
}