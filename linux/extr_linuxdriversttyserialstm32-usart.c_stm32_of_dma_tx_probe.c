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
struct uart_port {scalar_t__ mapbase; } ;
struct stm32_usart_offsets {scalar_t__ tdr; } ;
struct stm32_port {int tx_dma_busy; int /*<<< orphan*/ * tx_ch; int /*<<< orphan*/  tx_dma_buf; int /*<<< orphan*/  tx_buf; struct uart_port port; TYPE_1__* info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_addr_width; scalar_t__ dst_addr; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TX_BUF_L ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_slave_channel (struct device*,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,struct dma_slave_config*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_of_dma_tx_probe(struct stm32_port *stm32port,
				 struct platform_device *pdev)
{
	struct stm32_usart_offsets *ofs = &stm32port->info->ofs;
	struct uart_port *port = &stm32port->port;
	struct device *dev = &pdev->dev;
	struct dma_slave_config config;
	int ret;

	stm32port->tx_dma_busy = false;

	/* Request DMA TX channel */
	stm32port->tx_ch = dma_request_slave_channel(dev, "tx");
	if (!stm32port->tx_ch) {
		dev_info(dev, "tx dma alloc failed\n");
		return -ENODEV;
	}
	stm32port->tx_buf = dma_alloc_coherent(&pdev->dev, TX_BUF_L,
						 &stm32port->tx_dma_buf,
						 GFP_KERNEL);
	if (!stm32port->tx_buf) {
		ret = -ENOMEM;
		goto alloc_err;
	}

	/* Configure DMA channel */
	memset(&config, 0, sizeof(config));
	config.dst_addr = port->mapbase + ofs->tdr;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;

	ret = dmaengine_slave_config(stm32port->tx_ch, &config);
	if (ret < 0) {
		dev_err(dev, "tx dma channel config failed\n");
		ret = -ENODEV;
		goto config_err;
	}

	return 0;

config_err:
	dma_free_coherent(&pdev->dev,
			  TX_BUF_L, stm32port->tx_buf,
			  stm32port->tx_dma_buf);

alloc_err:
	dma_release_channel(stm32port->tx_ch);
	stm32port->tx_ch = NULL;

	return ret;
}