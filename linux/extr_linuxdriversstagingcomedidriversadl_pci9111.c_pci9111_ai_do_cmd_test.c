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
struct comedi_device {int /*<<< orphan*/  pacer; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; unsigned int start_arg; unsigned int convert_arg; unsigned int scan_begin_arg; unsigned int scan_end_arg; unsigned int chanlist_len; unsigned int stop_arg; scalar_t__ chanlist; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCI9111_AI_ACQUISITION_PERIOD_MIN_NS ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 int pci9111_ai_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

__attribute__((used)) static int pci9111_ai_do_cmd_test(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (cmd->scan_begin_src != TRIG_FOLLOW) {
		if (cmd->scan_begin_src != cmd->convert_src)
			err |= -EINVAL;
	}

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	if (cmd->convert_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
					PCI9111_AI_ACQUISITION_PERIOD_MIN_NS);
	} else {	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
					PCI9111_AI_ACQUISITION_PERIOD_MIN_NS);
	} else {	/* TRIG_FOLLOW || TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	}

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	}

	/*
	 * There's only one timer on this card, so the scan_begin timer
	 * must be a multiple of chanlist_len*convert_arg
	 */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->chanlist_len * cmd->convert_arg;

		if (arg < cmd->scan_begin_arg)
			arg *= (cmd->scan_begin_arg / arg);

		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci9111_ai_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}