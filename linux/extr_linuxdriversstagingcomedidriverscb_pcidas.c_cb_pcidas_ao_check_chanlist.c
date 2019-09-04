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
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cb_pcidas_ao_check_chanlist(struct comedi_device *dev,
				       struct comedi_subdevice *s,
				       struct comedi_cmd *cmd)
{
	unsigned int chan0 = CR_CHAN(cmd->chanlist[0]);

	if (cmd->chanlist_len > 1) {
		unsigned int chan1 = CR_CHAN(cmd->chanlist[1]);

		if (chan0 != 0 || chan1 != 1) {
			dev_dbg(dev->class_dev,
				"channels must be ordered channel 0, channel 1 in chanlist\n");
			return -EINVAL;
		}
	}

	return 0;
}