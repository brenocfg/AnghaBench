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
struct comedi_subdevice {scalar_t__ type; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int /*<<< orphan*/  I8255_SIZE ; 
 int /*<<< orphan*/  release_region (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long subdev_8255_regbase (struct comedi_subdevice*) ; 

__attribute__((used)) static void dev_8255_detach(struct comedi_device *dev)
{
	struct comedi_subdevice *s;
	int i;

	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		if (s->type != COMEDI_SUBD_UNUSED) {
			unsigned long regbase = subdev_8255_regbase(s);

			release_region(regbase, I8255_SIZE);
		}
	}
}