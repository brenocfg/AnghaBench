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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct s3c24xx_uart_port {TYPE_1__ port; struct s3c24xx_uart_dma* dma; } ;
struct s3c24xx_uart_dma {int /*<<< orphan*/ * tx_chan; int /*<<< orphan*/  tx_addr; int /*<<< orphan*/ * rx_chan; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  rx_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c24xx_serial_release_dma(struct s3c24xx_uart_port *p)
{
	struct s3c24xx_uart_dma	*dma = p->dma;

	if (dma->rx_chan) {
		dmaengine_terminate_all(dma->rx_chan);
		dma_unmap_single(p->port.dev, dma->rx_addr,
				dma->rx_size, DMA_FROM_DEVICE);
		kfree(dma->rx_buf);
		dma_release_channel(dma->rx_chan);
		dma->rx_chan = NULL;
	}

	if (dma->tx_chan) {
		dmaengine_terminate_all(dma->tx_chan);
		dma_unmap_single(p->port.dev, dma->tx_addr,
				UART_XMIT_SIZE, DMA_TO_DEVICE);
		dma_release_channel(dma->tx_chan);
		dma->tx_chan = NULL;
	}
}