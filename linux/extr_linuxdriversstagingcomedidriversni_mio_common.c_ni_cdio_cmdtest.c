#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int scan_begin_arg; scalar_t__ chanlist_len; scalar_t__ chanlist; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  scan_end_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  stop_src; int /*<<< orphan*/  scan_end_src; int /*<<< orphan*/  convert_src; int /*<<< orphan*/  scan_begin_src; int /*<<< orphan*/  start_src; } ;
struct TYPE_2__ {unsigned int prealloc_bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_INVERT ; 
 int CR_PACK_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NI_M_CDO_MODE_SAMPLE_SRC_MASK ; 
 int /*<<< orphan*/  TRIG_COUNT ; 
 int /*<<< orphan*/  TRIG_EXT ; 
 int /*<<< orphan*/  TRIG_INT ; 
 int /*<<< orphan*/  TRIG_NONE ; 
 int /*<<< orphan*/  TRIG_NOW ; 
 unsigned int comedi_bytes_per_scan_cmd (struct comedi_subdevice*,struct comedi_cmd*) ; 
 int comedi_check_trigger_arg_is (int /*<<< orphan*/ *,scalar_t__) ; 
 int comedi_check_trigger_arg_max (int /*<<< orphan*/ *,unsigned int) ; 
 int comedi_check_trigger_src (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ni_cdio_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

__attribute__((used)) static int ni_cdio_cmdtest(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	unsigned int bytes_per_scan;
	int err = 0;
	int tmp;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	tmp = cmd->scan_begin_arg;
	tmp &= CR_PACK_FLAGS(NI_M_CDO_MODE_SAMPLE_SRC_MASK, 0, 0, CR_INVERT);
	if (tmp != cmd->scan_begin_arg)
		err |= -EINVAL;

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	bytes_per_scan = comedi_bytes_per_scan_cmd(s, cmd);
	if (bytes_per_scan) {
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg,
						    s->async->prealloc_bufsz /
						    bytes_per_scan);
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list if it exists */

	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= ni_cdio_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}