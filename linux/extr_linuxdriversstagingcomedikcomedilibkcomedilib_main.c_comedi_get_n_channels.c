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
struct comedi_device {unsigned int n_subdevices; int /*<<< orphan*/  attach_lock; TYPE_1__* subdevices; int /*<<< orphan*/  attached; } ;
struct TYPE_2__ {int n_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int comedi_get_n_channels(struct comedi_device *dev, unsigned int subdevice)
{
	int n;

	down_read(&dev->attach_lock);
	if (!dev->attached || subdevice >= dev->n_subdevices)
		n = 0;
	else
		n = dev->subdevices[subdevice].n_chan;
	up_read(&dev->attach_lock);

	return n;
}