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
struct TYPE_4__ {size_t rx; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct dma_tx_state {scalar_t__ residue; } ;
struct dma_chan {int dummy; } ;
struct circ_buf {scalar_t__ head; scalar_t__ tail; scalar_t__ buf; } ;
struct atmel_uart_port {int /*<<< orphan*/  sg_rx; int /*<<< orphan*/  tasklet_rx; int /*<<< orphan*/  cookie_rx; struct dma_chan* chan_rx; struct circ_buf rx_ring; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int /*<<< orphan*/  ATMEL_US_STTTO ; 
 int /*<<< orphan*/  ATMEL_US_TIMEOUT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_ERROR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  atmel_tasklet_schedule (struct atmel_uart_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dmaengine_tx_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 scalar_t__ sg_dma_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,scalar_t__,size_t) ; 

__attribute__((used)) static void atmel_rx_from_dma(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct tty_port *tport = &port->state->port;
	struct circ_buf *ring = &atmel_port->rx_ring;
	struct dma_chan *chan = atmel_port->chan_rx;
	struct dma_tx_state state;
	enum dma_status dmastat;
	size_t count;


	/* Reset the UART timeout early so that we don't miss one */
	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_STTTO);
	dmastat = dmaengine_tx_status(chan,
				atmel_port->cookie_rx,
				&state);
	/* Restart a new tasklet if DMA status is error */
	if (dmastat == DMA_ERROR) {
		dev_dbg(port->dev, "Get residue error, restart tasklet\n");
		atmel_uart_writel(port, ATMEL_US_IER, ATMEL_US_TIMEOUT);
		atmel_tasklet_schedule(atmel_port, &atmel_port->tasklet_rx);
		return;
	}

	/* CPU claims ownership of RX DMA buffer */
	dma_sync_sg_for_cpu(port->dev,
			    &atmel_port->sg_rx,
			    1,
			    DMA_FROM_DEVICE);

	/*
	 * ring->head points to the end of data already written by the DMA.
	 * ring->tail points to the beginning of data to be read by the
	 * framework.
	 * The current transfer size should not be larger than the dma buffer
	 * length.
	 */
	ring->head = sg_dma_len(&atmel_port->sg_rx) - state.residue;
	BUG_ON(ring->head > sg_dma_len(&atmel_port->sg_rx));
	/*
	 * At this point ring->head may point to the first byte right after the
	 * last byte of the dma buffer:
	 * 0 <= ring->head <= sg_dma_len(&atmel_port->sg_rx)
	 *
	 * However ring->tail must always points inside the dma buffer:
	 * 0 <= ring->tail <= sg_dma_len(&atmel_port->sg_rx) - 1
	 *
	 * Since we use a ring buffer, we have to handle the case
	 * where head is lower than tail. In such a case, we first read from
	 * tail to the end of the buffer then reset tail.
	 */
	if (ring->head < ring->tail) {
		count = sg_dma_len(&atmel_port->sg_rx) - ring->tail;

		tty_insert_flip_string(tport, ring->buf + ring->tail, count);
		ring->tail = 0;
		port->icount.rx += count;
	}

	/* Finally we read data from tail to head */
	if (ring->tail < ring->head) {
		count = ring->head - ring->tail;

		tty_insert_flip_string(tport, ring->buf + ring->tail, count);
		/* Wrap ring->head if needed */
		if (ring->head >= sg_dma_len(&atmel_port->sg_rx))
			ring->head = 0;
		ring->tail = ring->head;
		port->icount.rx += count;
	}

	/* USART retreives ownership of RX DMA buffer */
	dma_sync_sg_for_device(port->dev,
			       &atmel_port->sg_rx,
			       1,
			       DMA_FROM_DEVICE);

	/*
	 * Drop the lock here since it might end up calling
	 * uart_start(), which takes the lock.
	 */
	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);

	atmel_uart_writel(port, ATMEL_US_IER, ATMEL_US_TIMEOUT);
}