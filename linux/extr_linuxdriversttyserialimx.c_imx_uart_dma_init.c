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
struct TYPE_4__ {scalar_t__ mapbase; struct device* dev; } ;
struct TYPE_3__ {scalar_t__ buf; } ;
struct imx_port {void* dma_chan_tx; TYPE_2__ port; scalar_t__ rx_buf; TYPE_1__ rx_ring; void* dma_chan_rx; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_maxburst; void* dst_addr_width; scalar_t__ dst_addr; int /*<<< orphan*/  direction; scalar_t__ src_maxburst; void* src_addr_width; scalar_t__ src_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 void* DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RXTL_DMA ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  TXTL_DMA ; 
 scalar_t__ URTX0 ; 
 scalar_t__ URXD0 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_request_slave_channel (struct device*,char*) ; 
 int dmaengine_slave_config (void*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  imx_uart_dma_exit (struct imx_port*) ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_uart_dma_init(struct imx_port *sport)
{
	struct dma_slave_config slave_config = {};
	struct device *dev = sport->port.dev;
	int ret;

	/* Prepare for RX : */
	sport->dma_chan_rx = dma_request_slave_channel(dev, "rx");
	if (!sport->dma_chan_rx) {
		dev_dbg(dev, "cannot get the DMA channel.\n");
		ret = -EINVAL;
		goto err;
	}

	slave_config.direction = DMA_DEV_TO_MEM;
	slave_config.src_addr = sport->port.mapbase + URXD0;
	slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	/* one byte less than the watermark level to enable the aging timer */
	slave_config.src_maxburst = RXTL_DMA - 1;
	ret = dmaengine_slave_config(sport->dma_chan_rx, &slave_config);
	if (ret) {
		dev_err(dev, "error in RX dma configuration.\n");
		goto err;
	}

	sport->rx_buf = kzalloc(RX_BUF_SIZE, GFP_KERNEL);
	if (!sport->rx_buf) {
		ret = -ENOMEM;
		goto err;
	}
	sport->rx_ring.buf = sport->rx_buf;

	/* Prepare for TX : */
	sport->dma_chan_tx = dma_request_slave_channel(dev, "tx");
	if (!sport->dma_chan_tx) {
		dev_err(dev, "cannot get the TX DMA channel!\n");
		ret = -EINVAL;
		goto err;
	}

	slave_config.direction = DMA_MEM_TO_DEV;
	slave_config.dst_addr = sport->port.mapbase + URTX0;
	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	slave_config.dst_maxburst = TXTL_DMA;
	ret = dmaengine_slave_config(sport->dma_chan_tx, &slave_config);
	if (ret) {
		dev_err(dev, "error in TX dma configuration.");
		goto err;
	}

	return 0;
err:
	imx_uart_dma_exit(sport);
	return ret;
}