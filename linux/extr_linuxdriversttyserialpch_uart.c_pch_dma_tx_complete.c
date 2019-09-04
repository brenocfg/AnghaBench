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
struct uart_port {int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct scatterlist {int dummy; } ;
struct eg20t_port {int nent; struct scatterlist* sg_tx_p; scalar_t__ tx_dma_use; int /*<<< orphan*/  desc_tx; struct uart_port port; } ;
struct circ_buf {int tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PCH_UART_HAL_TX_INT ; 
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  pch_uart_hal_enable_interrupt (struct eg20t_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void pch_dma_tx_complete(void *arg)
{
	struct eg20t_port *priv = arg;
	struct uart_port *port = &priv->port;
	struct circ_buf *xmit = &port->state->xmit;
	struct scatterlist *sg = priv->sg_tx_p;
	int i;

	for (i = 0; i < priv->nent; i++, sg++) {
		xmit->tail += sg_dma_len(sg);
		port->icount.tx += sg_dma_len(sg);
	}
	xmit->tail &= UART_XMIT_SIZE - 1;
	async_tx_ack(priv->desc_tx);
	dma_unmap_sg(port->dev, sg, priv->nent, DMA_TO_DEVICE);
	priv->tx_dma_use = 0;
	priv->nent = 0;
	kfree(priv->sg_tx_p);
	pch_uart_hal_enable_interrupt(priv, PCH_UART_HAL_TX_INT);
}