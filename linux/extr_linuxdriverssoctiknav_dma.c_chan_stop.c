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
struct knav_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  cfg; TYPE_1__* reg_rx_flow; } ;
struct knav_dma_cfg {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag_sel; int /*<<< orphan*/  tags; int /*<<< orphan*/  control; int /*<<< orphan*/ * thresh; int /*<<< orphan*/ * fdq_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_teardown (struct knav_dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* kdev ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chan_stop(struct knav_dma_chan *chan)
{
	spin_lock(&chan->lock);
	if (chan->reg_rx_flow) {
		/* first detach fdqs, starve out the flow */
		writel_relaxed(0, &chan->reg_rx_flow->fdq_sel[0]);
		writel_relaxed(0, &chan->reg_rx_flow->fdq_sel[1]);
		writel_relaxed(0, &chan->reg_rx_flow->thresh[0]);
		writel_relaxed(0, &chan->reg_rx_flow->thresh[1]);
		writel_relaxed(0, &chan->reg_rx_flow->thresh[2]);
	}

	/* teardown the dma channel */
	chan_teardown(chan);

	/* then disconnect the completion side */
	if (chan->reg_rx_flow) {
		writel_relaxed(0, &chan->reg_rx_flow->control);
		writel_relaxed(0, &chan->reg_rx_flow->tags);
		writel_relaxed(0, &chan->reg_rx_flow->tag_sel);
	}

	memset(&chan->cfg, 0, sizeof(struct knav_dma_cfg));
	spin_unlock(&chan->lock);

	dev_dbg(kdev->dev, "channel stopped\n");
}