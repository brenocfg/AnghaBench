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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct apci1500_private* private; } ;
struct apci1500_private {unsigned int* pm; unsigned int* pt; unsigned int* pp; } ;

/* Variables and functions */
#define  COMEDI_DIGITAL_TRIG_DISABLE 130 
#define  COMEDI_DIGITAL_TRIG_ENABLE_EDGES 129 
#define  COMEDI_DIGITAL_TRIG_ENABLE_LEVELS 128 
 int EINVAL ; 
 int comedi_check_trigger_is_unique (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int apci1500_di_cfg_trig(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct apci1500_private *devpriv = dev->private;
	unsigned int trig = data[1];
	unsigned int shift = data[3];
	unsigned int hi_mask = data[4] << shift;
	unsigned int lo_mask = data[5] << shift;
	unsigned int chan_mask = hi_mask | lo_mask;
	unsigned int old_mask = (1 << shift) - 1;
	unsigned int pm = devpriv->pm[trig] & old_mask;
	unsigned int pt = devpriv->pt[trig] & old_mask;
	unsigned int pp = devpriv->pp[trig] & old_mask;

	if (trig > 1) {
		dev_dbg(dev->class_dev,
			"invalid digital trigger number (0=AND, 1=OR)\n");
		return -EINVAL;
	}

	if (chan_mask > 0xffff) {
		dev_dbg(dev->class_dev, "invalid digital trigger channel\n");
		return -EINVAL;
	}

	switch (data[2]) {
	case COMEDI_DIGITAL_TRIG_DISABLE:
		/* clear trigger configuration */
		pm = 0;
		pt = 0;
		pp = 0;
		break;
	case COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
		pm |= chan_mask;	/* enable channels */
		pt |= chan_mask;	/* enable edge detection */
		pp |= hi_mask;		/* rising-edge channels */
		pp &= ~lo_mask;		/* falling-edge channels */
		break;
	case COMEDI_DIGITAL_TRIG_ENABLE_LEVELS:
		pm |= chan_mask;	/* enable channels */
		pt &= ~chan_mask;	/* enable level detection */
		pp |= hi_mask;		/* high level channels */
		pp &= ~lo_mask;		/* low level channels */
		break;
	default:
		return -EINVAL;
	}

	/*
	 * The AND mode trigger can only have one channel (max) enabled
	 * for edge detection.
	 */
	if (trig == 0) {
		int ret = 0;
		unsigned int src;

		src = pt & 0xff;
		if (src)
			ret |= comedi_check_trigger_is_unique(src);

		src = (pt >> 8) & 0xff;
		if (src)
			ret |= comedi_check_trigger_is_unique(src);

		if (ret) {
			dev_dbg(dev->class_dev,
				"invalid AND trigger configuration\n");
			return ret;
		}
	}

	/* save the trigger configuration */
	devpriv->pm[trig] = pm;
	devpriv->pt[trig] = pt;
	devpriv->pp[trig] = pp;

	return insn->n;
}