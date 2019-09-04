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
struct ni_660x_private {int /*<<< orphan*/ * io_cfg; int /*<<< orphan*/  interrupt_lock; int /*<<< orphan*/  mite_channel_lock; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int NI660X_NUM_PFI_CHANNELS ; 
 int /*<<< orphan*/  NI_660X_PFI_OUTPUT_COUNTER ; 
 struct ni_660x_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni_660x_allocate_private(struct comedi_device *dev)
{
	struct ni_660x_private *devpriv;
	unsigned int i;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	spin_lock_init(&devpriv->mite_channel_lock);
	spin_lock_init(&devpriv->interrupt_lock);
	for (i = 0; i < NI660X_NUM_PFI_CHANNELS; ++i)
		devpriv->io_cfg[i] = NI_660X_PFI_OUTPUT_COUNTER;

	return 0;
}