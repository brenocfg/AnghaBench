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
struct ni_private {int /*<<< orphan*/ * gpct_mite_ring; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int mite_buf_change (int /*<<< orphan*/ ,struct comedi_subdevice*) ; 

__attribute__((used)) static int pcimio_gpct0_change(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	struct ni_private *devpriv = dev->private;
	int ret;

	ret = mite_buf_change(devpriv->gpct_mite_ring[0], s);
	if (ret < 0)
		return ret;

	return 0;
}