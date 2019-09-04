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
struct dma_slave_caps {scalar_t__ residue_granularity; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_RESIDUE_GRANULARITY_DESCRIPTOR ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int dma_get_slave_caps (struct dma_chan*,struct dma_slave_caps*) ; 

__attribute__((used)) static bool dmaengine_pcm_can_report_residue(struct device *dev,
	struct dma_chan *chan)
{
	struct dma_slave_caps dma_caps;
	int ret;

	ret = dma_get_slave_caps(chan, &dma_caps);
	if (ret != 0) {
		dev_warn(dev, "Failed to get DMA channel capabilities, falling back to period counting: %d\n",
			 ret);
		return false;
	}

	if (dma_caps.residue_granularity == DMA_RESIDUE_GRANULARITY_DESCRIPTOR)
		return false;

	return true;
}