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
struct ni_gpct {size_t chip_index; size_t counter_index; } ;
struct ni_660x_private {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/  mite; struct mite_ring*** ring; } ;
struct mite_ring {int dummy; } ;
struct mite_channel {int dir; int /*<<< orphan*/  channel; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_660x_private* private; } ;
typedef  enum comedi_io_direction { ____Placeholder_comedi_io_direction } comedi_io_direction ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,struct mite_ring*) ; 
 int /*<<< orphan*/  ni_660x_set_dma_channel (struct comedi_device*,int /*<<< orphan*/ ,struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (struct ni_gpct*,struct mite_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_660x_request_mite_channel(struct comedi_device *dev,
					struct ni_gpct *counter,
					enum comedi_io_direction direction)
{
	struct ni_660x_private *devpriv = dev->private;
	struct mite_ring *ring;
	struct mite_channel *mite_chan;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	ring = devpriv->ring[counter->chip_index][counter->counter_index];
	mite_chan = mite_request_channel(devpriv->mite, ring);
	if (!mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for counter\n");
		return -EBUSY;
	}
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(counter, mite_chan);
	ni_660x_set_dma_channel(dev, mite_chan->channel, counter);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}