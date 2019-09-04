#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {unsigned int rx_bytes_requested; int /*<<< orphan*/  rx_dma_chan; TYPE_2__* rx_dma_desc; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/  rx_dma_buf_phys; TYPE_1__ uport; } ;
struct TYPE_5__ {struct tegra_uart_port* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 unsigned int TEGRA_UART_RX_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_uart_rx_dma_complete ; 

__attribute__((used)) static int tegra_uart_start_rx_dma(struct tegra_uart_port *tup)
{
	unsigned int count = TEGRA_UART_RX_DMA_BUFFER_SIZE;

	tup->rx_dma_desc = dmaengine_prep_slave_single(tup->rx_dma_chan,
				tup->rx_dma_buf_phys, count, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT);
	if (!tup->rx_dma_desc) {
		dev_err(tup->uport.dev, "Not able to get desc for Rx\n");
		return -EIO;
	}

	tup->rx_dma_desc->callback = tegra_uart_rx_dma_complete;
	tup->rx_dma_desc->callback_param = tup;
	dma_sync_single_for_device(tup->uport.dev, tup->rx_dma_buf_phys,
				count, DMA_TO_DEVICE);
	tup->rx_bytes_requested = count;
	tup->rx_cookie = dmaengine_submit(tup->rx_dma_desc);
	dma_async_issue_pending(tup->rx_dma_chan);
	return 0;
}