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
struct TYPE_4__ {int tx; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct sirfsoc_uart_port {int transfer_size; int /*<<< orphan*/  tx_dma_state; scalar_t__ tx_dma_addr; struct uart_port port; } ;
struct circ_buf {int tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  TX_DMA_IDLE ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_uart_tx_with_dma (struct sirfsoc_uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void sirfsoc_uart_tx_dma_complete_callback(void *param)
{
	struct sirfsoc_uart_port *sirfport = (struct sirfsoc_uart_port *)param;
	struct uart_port *port = &sirfport->port;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	xmit->tail = (xmit->tail + sirfport->transfer_size) &
				(UART_XMIT_SIZE - 1);
	port->icount.tx += sirfport->transfer_size;
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
	if (sirfport->tx_dma_addr)
		dma_unmap_single(port->dev, sirfport->tx_dma_addr,
				sirfport->transfer_size, DMA_TO_DEVICE);
	sirfport->tx_dma_state = TX_DMA_IDLE;
	sirfsoc_uart_tx_with_dma(sirfport);
	spin_unlock_irqrestore(&port->lock, flags);
}