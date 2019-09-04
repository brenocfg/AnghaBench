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
struct atmel_uart_port {int tx_stopped; int /*<<< orphan*/  tx_done_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int /*<<< orphan*/  ATMEL_PDC_TXTDIS ; 
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int /*<<< orphan*/  ATMEL_US_IDR ; 
 int /*<<< orphan*/  ATMEL_US_TXDIS ; 
 int /*<<< orphan*/  atmel_start_rx (struct uart_port*) ; 
 scalar_t__ atmel_uart_is_half_duplex (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atmel_use_pdc_tx (struct uart_port*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_stop_tx(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_pdc_tx(port)) {
		/* disable PDC transmit */
		atmel_uart_writel(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTDIS);
	}

	/*
	 * Disable the transmitter.
	 * This is mandatory when DMA is used, otherwise the DMA buffer
	 * is fully transmitted.
	 */
	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_TXDIS);
	atmel_port->tx_stopped = true;

	/* Disable interrupts */
	atmel_uart_writel(port, ATMEL_US_IDR, atmel_port->tx_done_mask);

	if (atmel_uart_is_half_duplex(port))
		atmel_start_rx(port);

}