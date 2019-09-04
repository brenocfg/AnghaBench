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
struct hsu_dma_slave {scalar_t__ dma_dev; scalar_t__ chan_id; } ;
struct dma_chan {scalar_t__ chan_id; struct hsu_dma_slave* private; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */

__attribute__((used)) static bool mid8250_dma_filter(struct dma_chan *chan, void *param)
{
	struct hsu_dma_slave *s = param;

	if (s->dma_dev != chan->device->dev || s->chan_id != chan->chan_id)
		return false;

	chan->private = s;
	return true;
}