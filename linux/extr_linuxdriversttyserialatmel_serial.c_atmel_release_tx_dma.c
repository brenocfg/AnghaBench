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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;
struct atmel_uart_port {int /*<<< orphan*/  cookie_tx; struct dma_chan* chan_tx; int /*<<< orphan*/ * desc_tx; int /*<<< orphan*/  sg_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_release_tx_dma(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct dma_chan *chan = atmel_port->chan_tx;

	if (chan) {
		dmaengine_terminate_all(chan);
		dma_release_channel(chan);
		dma_unmap_sg(port->dev, &atmel_port->sg_tx, 1,
				DMA_TO_DEVICE);
	}

	atmel_port->desc_tx = NULL;
	atmel_port->chan_tx = NULL;
	atmel_port->cookie_tx = -EINVAL;
}