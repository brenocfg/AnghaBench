#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int flags; unsigned int type; int /*<<< orphan*/  fifosize; } ;
struct uart_8250_port {TYPE_1__* dma; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  tx_loadsz; struct uart_port port; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_loadsz; int /*<<< orphan*/  fifo_size; } ;
struct TYPE_3__ {scalar_t__ rx_dma; scalar_t__ tx_dma; } ;

/* Variables and functions */
 int UPF_FIXED_TYPE ; 
 scalar_t__ serial8250_rx_dma ; 
 scalar_t__ serial8250_tx_dma ; 
 int /*<<< orphan*/  set_io_from_upio (struct uart_port*) ; 
 TYPE_2__* uart_config ; 

void serial8250_set_defaults(struct uart_8250_port *up)
{
	struct uart_port *port = &up->port;

	if (up->port.flags & UPF_FIXED_TYPE) {
		unsigned int type = up->port.type;

		if (!up->port.fifosize)
			up->port.fifosize = uart_config[type].fifo_size;
		if (!up->tx_loadsz)
			up->tx_loadsz = uart_config[type].tx_loadsz;
		if (!up->capabilities)
			up->capabilities = uart_config[type].flags;
	}

	set_io_from_upio(port);

	/* default dma handlers */
	if (up->dma) {
		if (!up->dma->tx_dma)
			up->dma->tx_dma = serial8250_tx_dma;
		if (!up->dma->rx_dma)
			up->dma->rx_dma = serial8250_rx_dma;
	}
}