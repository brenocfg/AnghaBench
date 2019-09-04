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
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct dma_chan {int dummy; } ;
struct circ_buf {int tail; } ;
struct atmel_uart_port {int hd_start_rx; int /*<<< orphan*/  tx_done_mask; int /*<<< orphan*/  tasklet_tx; int /*<<< orphan*/  lock_tx; int /*<<< orphan*/ * desc_tx; int /*<<< orphan*/  cookie_tx; scalar_t__ tx_len; struct dma_chan* chan_tx; struct uart_port uart; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int /*<<< orphan*/  EINVAL ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmel_tasklet_schedule (struct atmel_uart_port*,int /*<<< orphan*/ *) ; 
 scalar_t__ atmel_uart_is_half_duplex (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void atmel_complete_tx_dma(void *arg)
{
	struct atmel_uart_port *atmel_port = arg;
	struct uart_port *port = &atmel_port->uart;
	struct circ_buf *xmit = &port->state->xmit;
	struct dma_chan *chan = atmel_port->chan_tx;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	if (chan)
		dmaengine_terminate_all(chan);
	xmit->tail += atmel_port->tx_len;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += atmel_port->tx_len;

	spin_lock_irq(&atmel_port->lock_tx);
	async_tx_ack(atmel_port->desc_tx);
	atmel_port->cookie_tx = -EINVAL;
	atmel_port->desc_tx = NULL;
	spin_unlock_irq(&atmel_port->lock_tx);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	/*
	 * xmit is a circular buffer so, if we have just send data from
	 * xmit->tail to the end of xmit->buf, now we have to transmit the
	 * remaining data from the beginning of xmit->buf to xmit->head.
	 */
	if (!uart_circ_empty(xmit))
		atmel_tasklet_schedule(atmel_port, &atmel_port->tasklet_tx);
	else if (atmel_uart_is_half_duplex(port)) {
		/*
		 * DMA done, re-enable TXEMPTY and signal that we can stop
		 * TX and start RX for RS485
		 */
		atmel_port->hd_start_rx = true;
		atmel_uart_writel(port, ATMEL_US_IER,
				  atmel_port->tx_done_mask);
	}

	spin_unlock_irqrestore(&port->lock, flags);
}