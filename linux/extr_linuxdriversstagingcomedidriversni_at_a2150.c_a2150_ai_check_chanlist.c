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

/* Variables and functions */
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int a2150_ai_check_chanlist(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_cmd *cmd)
{
	unsigned int chan0 = CR_CHAN(cmd->chanlist[0]);
	unsigned int aref0 = CR_AREF(cmd->chanlist[0]);
	int i;

	if (cmd->chanlist_len == 2 && (chan0 == 1 || chan0 == 3)) {
		dev_dbg(dev->class_dev,
			"length 2 chanlist must be channels 0,1 or channels 2,3\n");
		return -EINVAL;
	}

	if (cmd->chanlist_len == 3) {
		dev_dbg(dev->class_dev,
			"chanlist must have 1,2 or 4 channels\n");
		return -EINVAL;
	}

	for (i = 1; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int aref = CR_AREF(cmd->chanlist[i]);

		if (chan != (chan0 + i)) {
			dev_dbg(dev->class_dev,
				"entries in chanlist must be consecutive channels, counting upwards\n");
			return -EINVAL;
		}

		if (chan == 2)
			aref0 = aref;
		if (aref != aref0) {
			dev_dbg(dev->class_dev,
				"channels 0/1 and 2/3 must have the same analog reference\n");
			return -EINVAL;
		}
	}

	return 0;
}