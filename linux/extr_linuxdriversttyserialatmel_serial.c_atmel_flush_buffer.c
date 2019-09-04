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
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ ofs; } ;
struct atmel_uart_port {scalar_t__ tx_len; TYPE_1__ pdc_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_TCR ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atmel_use_pdc_tx (struct uart_port*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_flush_buffer(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_pdc_tx(port)) {
		atmel_uart_writel(port, ATMEL_PDC_TCR, 0);
		atmel_port->pdc_tx.ofs = 0;
	}
	/*
	 * in uart_flush_buffer(), the xmit circular buffer has just
	 * been cleared, so we have to reset tx_len accordingly.
	 */
	atmel_port->tx_len = 0;
}