#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int src_maxburst; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr; scalar_t__ src_addr; int /*<<< orphan*/  direction; } ;
struct stm32_spdifrx_data {int /*<<< orphan*/ * ctrl_chan; TYPE_3__ slave_config; TYPE_2__* dmab; scalar_t__ phys_addr; } ;
struct snd_dma_buffer {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; struct device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_IRAM ; 
 int /*<<< orphan*/  SPDIFRX_CSR_BUF_LENGTH ; 
 scalar_t__ STM32_SPDIFRX_CSR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 TYPE_2__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_request_chan (struct device*,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int stm32_spdifrx_dma_ctrl_register(struct device *dev,
					   struct stm32_spdifrx_data *spdifrx)
{
	int ret;

	spdifrx->ctrl_chan = dma_request_chan(dev, "rx-ctrl");
	if (IS_ERR(spdifrx->ctrl_chan)) {
		dev_err(dev, "dma_request_slave_channel failed\n");
		return PTR_ERR(spdifrx->ctrl_chan);
	}

	spdifrx->dmab = devm_kzalloc(dev, sizeof(struct snd_dma_buffer),
				     GFP_KERNEL);
	if (!spdifrx->dmab)
		return -ENOMEM;

	spdifrx->dmab->dev.type = SNDRV_DMA_TYPE_DEV_IRAM;
	spdifrx->dmab->dev.dev = dev;
	ret = snd_dma_alloc_pages(spdifrx->dmab->dev.type, dev,
				  SPDIFRX_CSR_BUF_LENGTH, spdifrx->dmab);
	if (ret < 0) {
		dev_err(dev, "snd_dma_alloc_pages returned error %d\n", ret);
		return ret;
	}

	spdifrx->slave_config.direction = DMA_DEV_TO_MEM;
	spdifrx->slave_config.src_addr = (dma_addr_t)(spdifrx->phys_addr +
					 STM32_SPDIFRX_CSR);
	spdifrx->slave_config.dst_addr = spdifrx->dmab->addr;
	spdifrx->slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	spdifrx->slave_config.src_maxburst = 1;

	ret = dmaengine_slave_config(spdifrx->ctrl_chan,
				     &spdifrx->slave_config);
	if (ret < 0) {
		dev_err(dev, "dmaengine_slave_config returned error %d\n", ret);
		spdifrx->ctrl_chan = NULL;
	}

	return ret;
}