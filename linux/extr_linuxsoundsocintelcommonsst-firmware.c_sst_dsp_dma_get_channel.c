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
struct sst_dsp {int /*<<< orphan*/  dev; struct sst_dma* dma; } ;
struct sst_dma {int /*<<< orphan*/ * ch; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  direction; } ;
typedef  int /*<<< orphan*/  slave ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EIO ; 
 int /*<<< orphan*/  SST_DSP_DMA_MAX_BURST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_filter ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sst_dsp*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,struct dma_slave_config*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

int sst_dsp_dma_get_channel(struct sst_dsp *dsp, int chan_id)
{
	struct sst_dma *dma = dsp->dma;
	struct dma_slave_config slave;
	dma_cap_mask_t mask;
	int ret;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dma->ch = dma_request_channel(mask, dma_chan_filter, dsp);
	if (dma->ch == NULL) {
		dev_err(dsp->dev, "error: DMA request channel failed\n");
		return -EIO;
	}

	memset(&slave, 0, sizeof(slave));
	slave.direction = DMA_MEM_TO_DEV;
	slave.src_addr_width =
		slave.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	slave.src_maxburst = slave.dst_maxburst = SST_DSP_DMA_MAX_BURST;

	ret = dmaengine_slave_config(dma->ch, &slave);
	if (ret) {
		dev_err(dsp->dev, "error: unable to set DMA slave config %d\n",
			ret);
		dma_release_channel(dma->ch);
		dma->ch = NULL;
	}

	return ret;
}