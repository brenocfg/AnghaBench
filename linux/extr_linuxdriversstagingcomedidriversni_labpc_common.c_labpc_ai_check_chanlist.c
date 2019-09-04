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
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  MODE_MULT_CHAN_DOWN 131 
#define  MODE_MULT_CHAN_UP 130 
#define  MODE_SINGLE_CHAN 129 
#define  MODE_SINGLE_CHAN_INTERVAL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int labpc_ai_scan_mode (struct comedi_cmd*) ; 

__attribute__((used)) static int labpc_ai_check_chanlist(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_cmd *cmd)
{
	enum scan_mode mode = labpc_ai_scan_mode(cmd);
	unsigned int chan0 = CR_CHAN(cmd->chanlist[0]);
	unsigned int range0 = CR_RANGE(cmd->chanlist[0]);
	unsigned int aref0 = CR_AREF(cmd->chanlist[0]);
	int i;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int range = CR_RANGE(cmd->chanlist[i]);
		unsigned int aref = CR_AREF(cmd->chanlist[i]);

		switch (mode) {
		case MODE_SINGLE_CHAN:
			break;
		case MODE_SINGLE_CHAN_INTERVAL:
			if (chan != chan0) {
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				return -EINVAL;
			}
			break;
		case MODE_MULT_CHAN_UP:
			if (chan != i) {
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				return -EINVAL;
			}
			break;
		case MODE_MULT_CHAN_DOWN:
			if (chan != (cmd->chanlist_len - i - 1)) {
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				return -EINVAL;
			}
			break;
		}

		if (range != range0) {
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same range\n");
			return -EINVAL;
		}

		if (aref != aref0) {
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same reference\n");
			return -EINVAL;
		}
	}

	return 0;
}