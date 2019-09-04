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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/  ai_mite_chan; scalar_t__ is_628x; scalar_t__ is_6143; scalar_t__ is_611x; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; struct ni_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  prealloc_bufsz; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_arm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_prep_dma (int /*<<< orphan*/ ,int,int) ; 
 int ni_request_ai_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_ai_setup_MITE_dma(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	int retval;
	unsigned long flags;

	retval = ni_request_ai_mite_channel(dev);
	if (retval)
		return retval;

	/* write alloc the entire buffer */
	comedi_buf_write_alloc(s, s->async->prealloc_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (!devpriv->ai_mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		return -EIO;
	}

	if (devpriv->is_611x || devpriv->is_6143)
		mite_prep_dma(devpriv->ai_mite_chan, 32, 16);
	else if (devpriv->is_628x)
		mite_prep_dma(devpriv->ai_mite_chan, 32, 32);
	else
		mite_prep_dma(devpriv->ai_mite_chan, 16, 16);

	/*start the MITE */
	mite_dma_arm(devpriv->ai_mite_chan);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	return 0;
}