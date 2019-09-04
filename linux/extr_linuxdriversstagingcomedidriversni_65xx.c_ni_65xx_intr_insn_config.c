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
struct comedi_device {int dummy; } ;

/* Variables and functions */
#define  COMEDI_DIGITAL_TRIG_DISABLE 131 
#define  COMEDI_DIGITAL_TRIG_ENABLE_EDGES 130 
 int EINVAL ; 
#define  INSN_CONFIG_CHANGE_NOTIFY 129 
#define  INSN_CONFIG_DIGITAL_TRIG 128 
 int /*<<< orphan*/  ni_65xx_disable_edge_detection (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_65xx_update_edge_detection (struct comedi_device*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_65xx_intr_insn_config(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_CHANGE_NOTIFY:
		/* add instruction to check_insn_config_length() */
		if (insn->n != 3)
			return -EINVAL;

		/* update edge detection for channels 0 to 31 */
		ni_65xx_update_edge_detection(dev, 0, data[1], data[2]);
		/* clear edge detection for channels 32 to 63 */
		ni_65xx_update_edge_detection(dev, 32, 0, 0);
		/* clear edge detection for channels 64 to 95 */
		ni_65xx_update_edge_detection(dev, 64, 0, 0);
		break;
	case INSN_CONFIG_DIGITAL_TRIG:
		/* check trigger number */
		if (data[1] != 0)
			return -EINVAL;
		/* check digital trigger operation */
		switch (data[2]) {
		case COMEDI_DIGITAL_TRIG_DISABLE:
			ni_65xx_disable_edge_detection(dev);
			break;
		case COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			/*
			 * update edge detection for channels data[3]
			 * to (data[3] + 31)
			 */
			ni_65xx_update_edge_detection(dev, data[3],
						      data[4], data[5]);
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}