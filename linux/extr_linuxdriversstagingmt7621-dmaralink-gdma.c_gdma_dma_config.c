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
struct gdma_dmaengine_chan {void* burst_size; int /*<<< orphan*/  fifo_addr; int /*<<< orphan*/  slave_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct gdma_dma_dev {TYPE_1__ ddev; } ;
struct dma_slave_config {int direction; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  slave_id; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  dst_addr_width; scalar_t__ device_fc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct gdma_dma_dev* gdma_dma_chan_get_dev (struct gdma_dmaengine_chan*) ; 
 void* gdma_dma_maxburst (int /*<<< orphan*/ ) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int gdma_dma_config(struct dma_chan *c,
			   struct dma_slave_config *config)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);

	if (config->device_fc) {
		dev_err(dma_dev->ddev.dev, "not support flow controller\n");
		return -EINVAL;
	}

	switch (config->direction) {
	case DMA_MEM_TO_DEV:
		if (config->dst_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) {
			dev_err(dma_dev->ddev.dev, "only support 4 byte buswidth\n");
			return -EINVAL;
		}
		chan->slave_id = config->slave_id;
		chan->fifo_addr = config->dst_addr;
		chan->burst_size = gdma_dma_maxburst(config->dst_maxburst);
		break;
	case DMA_DEV_TO_MEM:
		if (config->src_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) {
			dev_err(dma_dev->ddev.dev, "only support 4 byte buswidth\n");
			return -EINVAL;
		}
		chan->slave_id = config->slave_id;
		chan->fifo_addr = config->src_addr;
		chan->burst_size = gdma_dma_maxburst(config->src_maxburst);
		break;
	default:
		dev_err(dma_dev->ddev.dev, "direction type %d error\n",
			config->direction);
		return -EINVAL;
	}

	return 0;
}