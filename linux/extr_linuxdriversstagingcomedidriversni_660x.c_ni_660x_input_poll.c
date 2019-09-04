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
struct ni_gpct {int /*<<< orphan*/  mite_chan; } ;
struct ni_660x_private {int /*<<< orphan*/  interrupt_lock; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct comedi_device {struct ni_660x_private* private; } ;

/* Variables and functions */
 int comedi_buf_read_n_available (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  mite_sync_dma (int /*<<< orphan*/ ,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_660x_input_poll(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct ni_660x_private *devpriv = dev->private;
	struct ni_gpct *counter = s->private;
	unsigned long flags;

	/* lock to avoid race with comedi_poll */
	spin_lock_irqsave(&devpriv->interrupt_lock, flags);
	mite_sync_dma(counter->mite_chan, s);
	spin_unlock_irqrestore(&devpriv->interrupt_lock, flags);
	return comedi_buf_read_n_available(s);
}