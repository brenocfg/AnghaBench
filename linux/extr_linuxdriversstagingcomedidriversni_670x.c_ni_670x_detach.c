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
struct comedi_subdevice {int /*<<< orphan*/  range_table_list; } ;
struct comedi_device {struct comedi_subdevice* subdevices; scalar_t__ n_subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_670x_detach(struct comedi_device *dev)
{
	struct comedi_subdevice *s;

	comedi_pci_detach(dev);
	if (dev->n_subdevices) {
		s = &dev->subdevices[0];
		if (s)
			kfree(s->range_table_list);
	}
}