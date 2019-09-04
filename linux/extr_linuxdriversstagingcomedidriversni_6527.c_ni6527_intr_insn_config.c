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
struct comedi_subdevice {unsigned int n_chan; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
#define  COMEDI_DIGITAL_TRIG_DISABLE 131 
#define  COMEDI_DIGITAL_TRIG_ENABLE_EDGES 130 
 int EINVAL ; 
#define  INSN_CONFIG_CHANGE_NOTIFY 129 
#define  INSN_CONFIG_DIGITAL_TRIG 128 
 int /*<<< orphan*/  ni6527_set_edge_detection (struct comedi_device*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni6527_intr_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int mask = 0xffffffff;
	unsigned int rising, falling, shift;

	switch (data[0]) {
	case INSN_CONFIG_CHANGE_NOTIFY:
		/* check_insn_config_length() does not check this instruction */
		if (insn->n != 3)
			return -EINVAL;
		rising = data[1];
		falling = data[2];
		ni6527_set_edge_detection(dev, mask, rising, falling);
		break;
	case INSN_CONFIG_DIGITAL_TRIG:
		/* check trigger number */
		if (data[1] != 0)
			return -EINVAL;
		/* check digital trigger operation */
		switch (data[2]) {
		case COMEDI_DIGITAL_TRIG_DISABLE:
			rising = 0;
			falling = 0;
			break;
		case COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			/* check shift amount */
			shift = data[3];
			if (shift >= s->n_chan) {
				mask = 0;
				rising = 0;
				falling = 0;
			} else {
				mask <<= shift;
				rising = data[4] << shift;
				falling = data[5] << shift;
			}
			break;
		default:
			return -EINVAL;
		}
		ni6527_set_edge_detection(dev, mask, rising, falling);
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}