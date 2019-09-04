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
struct ni_gpct {int /*<<< orphan*/  counter_dev; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  scan_end_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  start_arg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TRIG_COUNT ; 
#define  TRIG_EXT 131 
 unsigned int TRIG_FOLLOW ; 
#define  TRIG_INT 130 
 unsigned int TRIG_NONE ; 
#define  TRIG_NOW 129 
#define  TRIG_OTHER 128 
 int comedi_check_trigger_arg_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_is_unique (unsigned int) ; 
 int comedi_check_trigger_src (unsigned int*,unsigned int) ; 
 scalar_t__ ni_tio_counting_mode_registers_present (int /*<<< orphan*/ ) ; 

int ni_tio_cmdtest(struct comedi_device *dev,
		   struct comedi_subdevice *s,
		   struct comedi_cmd *cmd)
{
	struct ni_gpct *counter = s->private;
	int err = 0;
	unsigned int sources;

	/* Step 1 : check if triggers are trivially valid */

	sources = TRIG_NOW | TRIG_INT | TRIG_OTHER;
	if (ni_tio_counting_mode_registers_present(counter->counter_dev))
		sources |= TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->start_src, sources);

	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_EXT | TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_NOW | TRIG_EXT | TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);

	/* Step 2b : and mutually compatible */

	if (cmd->convert_src != TRIG_NOW && cmd->scan_begin_src != TRIG_FOLLOW)
		err |= -EINVAL;

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	switch (cmd->start_src) {
	case TRIG_NOW:
	case TRIG_INT:
	case TRIG_OTHER:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		break;
	case TRIG_EXT:
		/* start_arg is the start_trigger passed to ni_tio_arm() */
		break;
	}

	if (cmd->scan_begin_src != TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	if (cmd->convert_src != TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list if it exists */

	return 0;
}