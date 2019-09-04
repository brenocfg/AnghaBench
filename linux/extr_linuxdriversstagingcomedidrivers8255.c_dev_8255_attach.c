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
struct comedi_subdevice {void* type; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  class_dev; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 int COMEDI_NDEVCONFOPTS ; 
 void* COMEDI_SUBD_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  I8255_SIZE ; 
 int __comedi_request_region (struct comedi_device*,unsigned long,int /*<<< orphan*/ ) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_region (unsigned long,int /*<<< orphan*/ ) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dev_8255_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase;
	int ret;
	int i;

	for (i = 0; i < COMEDI_NDEVCONFOPTS; i++) {
		iobase = it->options[i];
		if (!iobase)
			break;
	}
	if (i == 0) {
		dev_warn(dev->class_dev, "no devices specified\n");
		return -EINVAL;
	}

	ret = comedi_alloc_subdevices(dev, i);
	if (ret)
		return ret;

	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		iobase = it->options[i];

		/*
		 * __comedi_request_region() does not set dev->iobase.
		 *
		 * For 8255 devices that are manually attached using
		 * comedi_config, the 'iobase' is the actual I/O port
		 * base address of the chip.
		 */
		ret = __comedi_request_region(dev, iobase, I8255_SIZE);
		if (ret) {
			s->type = COMEDI_SUBD_UNUSED;
		} else {
			ret = subdev_8255_init(dev, s, NULL, iobase);
			if (ret) {
				/*
				 * Release the I/O port region here, as the
				 * "detach" handler cannot find it.
				 */
				release_region(iobase, I8255_SIZE);
				s->type = COMEDI_SUBD_UNUSED;
				return ret;
			}
		}
	}

	return 0;
}