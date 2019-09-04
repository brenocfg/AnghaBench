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
struct comedi_subdevice {int subdev_flags; int n_chan; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int SDF_DIFF ; 
 int /*<<< orphan*/  comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int me4000_ai_check_chanlist(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_cmd *cmd)
{
	unsigned int aref0 = CR_AREF(cmd->chanlist[0]);
	int i;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int range = CR_RANGE(cmd->chanlist[i]);
		unsigned int aref = CR_AREF(cmd->chanlist[i]);

		if (aref != aref0) {
			dev_dbg(dev->class_dev,
				"Mode is not equal for all entries\n");
			return -EINVAL;
		}

		if (aref == AREF_DIFF) {
			if (!(s->subdev_flags & SDF_DIFF)) {
				dev_err(dev->class_dev,
					"Differential inputs are not available\n");
				return -EINVAL;
			}

			if (chan >= (s->n_chan / 2)) {
				dev_dbg(dev->class_dev,
					"Channel number to high\n");
				return -EINVAL;
			}

			if (!comedi_range_is_bipolar(s, range)) {
				dev_dbg(dev->class_dev,
					"Bipolar is not selected in differential mode\n");
				return -EINVAL;
			}
		}
	}

	return 0;
}