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
struct nidio96_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ di_mite_chan; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct nidio96_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  prealloc_bufsz; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_arm (scalar_t__) ; 
 int /*<<< orphan*/  mite_prep_dma (scalar_t__,int,int) ; 
 int ni_pcidio_request_di_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int setup_mite_dma(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct nidio96_private *devpriv = dev->private;
	int retval;
	unsigned long flags;

	retval = ni_pcidio_request_di_mite_channel(dev);
	if (retval)
		return retval;

	/* write alloc the entire buffer */
	comedi_buf_write_alloc(s, s->async->prealloc_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->di_mite_chan) {
		mite_prep_dma(devpriv->di_mite_chan, 32, 32);
		mite_dma_arm(devpriv->di_mite_chan);
	} else {
		retval = -EIO;
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	return retval;
}