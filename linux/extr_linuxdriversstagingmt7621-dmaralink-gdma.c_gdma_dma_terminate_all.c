#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct gdma_dmaengine_chan {int /*<<< orphan*/  id; TYPE_2__ vchan; int /*<<< orphan*/ * desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct gdma_dma_dev {TYPE_1__ ddev; int /*<<< orphan*/  chan_issued; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDMA_REG_CTRL0 (int /*<<< orphan*/ ) ; 
 int GDMA_REG_CTRL0_ENABLE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct gdma_dma_dev* gdma_dma_chan_get_dev (struct gdma_dmaengine_chan*) ; 
 int gdma_dma_read (struct gdma_dma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdma_dma_write (struct gdma_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gdma_dma_terminate_all(struct dma_chan *c)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	unsigned long flags, timeout;
	LIST_HEAD(head);
	int i = 0;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	chan->desc = NULL;
	clear_bit(chan->id, &dma_dev->chan_issued);
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_free_list(&chan->vchan, &head);

	/* wait dma transfer complete */
	timeout = jiffies + msecs_to_jiffies(5000);
	while (gdma_dma_read(dma_dev, GDMA_REG_CTRL0(chan->id)) &
			GDMA_REG_CTRL0_ENABLE) {
		if (time_after_eq(jiffies, timeout)) {
			dev_err(dma_dev->ddev.dev, "chan %d wait timeout\n",
				chan->id);
			/* restore to init value */
			gdma_dma_write(dma_dev, GDMA_REG_CTRL0(chan->id), 0);
			break;
		}
		cpu_relax();
		i++;
	}

	if (i)
		dev_dbg(dma_dev->ddev.dev, "terminate chan %d loops %d\n",
			chan->id, i);

	return 0;
}