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
struct knav_dma_chan {TYPE_1__* reg_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 unsigned long DMA_ENABLE ; 
 int /*<<< orphan*/  DMA_TEARDOWN ; 
 int /*<<< orphan*/  DMA_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 TYPE_2__* kdev ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chan_teardown(struct knav_dma_chan *chan)
{
	unsigned long end, value;

	if (!chan->reg_chan)
		return 0;

	/* indicate teardown */
	writel_relaxed(DMA_TEARDOWN, &chan->reg_chan->control);

	/* wait for the dma to shut itself down */
	end = jiffies + msecs_to_jiffies(DMA_TIMEOUT);
	do {
		value = readl_relaxed(&chan->reg_chan->control);
		if ((value & DMA_ENABLE) == 0)
			break;
	} while (time_after(end, jiffies));

	if (readl_relaxed(&chan->reg_chan->control) & DMA_ENABLE) {
		dev_err(kdev->dev, "timeout waiting for teardown\n");
		return -ETIMEDOUT;
	}

	return 0;
}