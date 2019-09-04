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
struct ni_660x_private {unsigned int* io_cfg; unsigned long long io_dir; } ;
struct comedi_device {struct ni_660x_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NI_660X_PFI_OUTPUT_COUNTER 129 
#define  NI_660X_PFI_OUTPUT_DIO 128 
 int /*<<< orphan*/  ni_660x_select_pfi_output (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_660x_set_pfi_routing(struct comedi_device *dev,
				   unsigned int chan, unsigned int source)
{
	struct ni_660x_private *devpriv = dev->private;

	switch (source) {
	case NI_660X_PFI_OUTPUT_COUNTER:
		if (chan < 8)
			return -EINVAL;
		break;
	case NI_660X_PFI_OUTPUT_DIO:
		if (chan > 31)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	devpriv->io_cfg[chan] = source;
	if (devpriv->io_dir & (1ULL << chan))
		ni_660x_select_pfi_output(dev, chan, devpriv->io_cfg[chan]);
	return 0;
}