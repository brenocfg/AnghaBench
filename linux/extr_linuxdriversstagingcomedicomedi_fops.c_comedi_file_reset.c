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
struct file {struct comedi_file* private_data; } ;
struct comedi_subdevice {int subdev_flags; } ;
struct comedi_file {int /*<<< orphan*/  write_subdev; int /*<<< orphan*/  read_subdev; int /*<<< orphan*/  last_detach_count; int /*<<< orphan*/  last_attached; struct comedi_device* dev; } ;
struct comedi_device {int /*<<< orphan*/  detach_count; int /*<<< orphan*/  attached; struct comedi_subdevice* write_subdev; struct comedi_subdevice* read_subdev; } ;

/* Variables and functions */
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 int SDF_CMD_READ ; 
 int SDF_CMD_WRITE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct comedi_subdevice*) ; 
 struct comedi_subdevice* comedi_subdevice_from_minor (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 unsigned int iminor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void comedi_file_reset(struct file *file)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_device *dev = cfp->dev;
	struct comedi_subdevice *s, *read_s, *write_s;
	unsigned int minor = iminor(file_inode(file));

	read_s = dev->read_subdev;
	write_s = dev->write_subdev;
	if (minor >= COMEDI_NUM_BOARD_MINORS) {
		s = comedi_subdevice_from_minor(dev, minor);
		if (!s || s->subdev_flags & SDF_CMD_READ)
			read_s = s;
		if (!s || s->subdev_flags & SDF_CMD_WRITE)
			write_s = s;
	}
	cfp->last_attached = dev->attached;
	cfp->last_detach_count = dev->detach_count;
	WRITE_ONCE(cfp->read_subdev, read_s);
	WRITE_ONCE(cfp->write_subdev, write_s);
}