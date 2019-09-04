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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; unsigned int start_arg; int scan_begin_arg; unsigned int convert_arg; unsigned int scan_end_arg; unsigned int chanlist_len; int stop_arg; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CR_EDGE ; 
 int CR_INVERT ; 
 int EINVAL ; 
 int TIMER_BASE ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_min (int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 int /*<<< orphan*/  ni_pcidio_ns_to_timer (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_pcidio_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#define MAX_SPEED	(TIMER_BASE)	/* in nanoseconds */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    MAX_SPEED);
		/* no minimum speed */
	} else {
		/* TRIG_EXT */
		/* should be level/edge, hi/lo specification here */
		if ((cmd->scan_begin_arg & ~(CR_EDGE | CR_INVERT)) != 0) {
			cmd->scan_begin_arg &= (CR_EDGE | CR_INVERT);
			err |= -EINVAL;
		}
	}

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->scan_begin_arg;
		ni_pcidio_ns_to_timer(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (err)
		return 4;

	return 0;
}