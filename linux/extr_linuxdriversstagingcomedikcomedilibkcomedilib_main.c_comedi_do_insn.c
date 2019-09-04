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
struct comedi_subdevice {scalar_t__ type; int (* insn_bits ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;int (* insn_config ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;struct comedi_device* busy; } ;
struct comedi_insn {size_t subdev; int insn; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {size_t n_subdevices; int /*<<< orphan*/  mutex; int /*<<< orphan*/  class_dev; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
#define  INSN_BITS 129 
#define  INSN_CONFIG 128 
 int comedi_check_chanlist (struct comedi_subdevice*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int stub2 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 

__attribute__((used)) static int comedi_do_insn(struct comedi_device *dev,
			  struct comedi_insn *insn,
			  unsigned int *data)
{
	struct comedi_subdevice *s;
	int ret;

	mutex_lock(&dev->mutex);

	if (!dev->attached) {
		ret = -EINVAL;
		goto error;
	}

	/* a subdevice instruction */
	if (insn->subdev >= dev->n_subdevices) {
		ret = -EINVAL;
		goto error;
	}
	s = &dev->subdevices[insn->subdev];

	if (s->type == COMEDI_SUBD_UNUSED) {
		dev_err(dev->class_dev,
			"%d not usable subdevice\n", insn->subdev);
		ret = -EIO;
		goto error;
	}

	/* XXX check lock */

	ret = comedi_check_chanlist(s, 1, &insn->chanspec);
	if (ret < 0) {
		dev_err(dev->class_dev, "bad chanspec\n");
		ret = -EINVAL;
		goto error;
	}

	if (s->busy) {
		ret = -EBUSY;
		goto error;
	}
	s->busy = dev;

	switch (insn->insn) {
	case INSN_BITS:
		ret = s->insn_bits(dev, s, insn, data);
		break;
	case INSN_CONFIG:
		/* XXX should check instruction length */
		ret = s->insn_config(dev, s, insn, data);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	s->busy = NULL;
error:

	mutex_unlock(&dev->mutex);
	return ret;
}