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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; TYPE_1__ xmit; } ;
struct sirfsoc_uart_port {scalar_t__ tx_dma_chan; TYPE_2__ rx_dma_items; scalar_t__ rx_dma_chan; struct uart_port port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIRFSOC_RX_DMA_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 struct sirfsoc_uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sirfsoc_uart_drv ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int sirfsoc_uart_remove(struct platform_device *pdev)
{
	struct sirfsoc_uart_port *sirfport = platform_get_drvdata(pdev);
	struct uart_port *port = &sirfport->port;
	uart_remove_one_port(&sirfsoc_uart_drv, port);
	if (sirfport->rx_dma_chan) {
		dmaengine_terminate_all(sirfport->rx_dma_chan);
		dma_release_channel(sirfport->rx_dma_chan);
		dma_free_coherent(port->dev, SIRFSOC_RX_DMA_BUF_SIZE,
				sirfport->rx_dma_items.xmit.buf,
				sirfport->rx_dma_items.dma_addr);
	}
	if (sirfport->tx_dma_chan) {
		dmaengine_terminate_all(sirfport->tx_dma_chan);
		dma_release_channel(sirfport->tx_dma_chan);
	}
	return 0;
}