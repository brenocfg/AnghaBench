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
struct sst_dsp {scalar_t__ dma_dev; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */

__attribute__((used)) static bool dma_chan_filter(struct dma_chan *chan, void *param)
{
	struct sst_dsp *dsp = (struct sst_dsp *)param;

	return chan->device->dev == dsp->dma_dev;
}