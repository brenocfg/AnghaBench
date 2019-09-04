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
struct dt3k_boardtype {unsigned int ai_speed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct dt3k_boardtype* board_ptr; } ;
struct comedi_cmd {scalar_t__ start_src; scalar_t__ scan_begin_src; scalar_t__ convert_src; scalar_t__ scan_end_src; scalar_t__ stop_src; unsigned int start_arg; unsigned int scan_begin_arg; unsigned int convert_arg; unsigned int scan_end_arg; unsigned int chanlist_len; unsigned int stop_arg; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (unsigned int*,int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_src (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  dt3k_ns_to_timer (int,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt3k_ai_cmdtest(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	const struct dt3k_boardtype *board = dev->board_ptr;
	int err = 0;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ai_speed);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    100 * 16 * 65535);
	}

	if (cmd->convert_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
						    50 * 16 * 65535);
	}

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg, 0x00ffffff);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->scan_begin_arg;
		dt3k_ns_to_timer(100, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (cmd->convert_src == TRIG_TIMER) {
		arg = cmd->convert_arg;
		dt3k_ns_to_timer(50, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		if (cmd->scan_begin_src == TRIG_TIMER) {
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_min(&cmd->
							    scan_begin_arg,
							    arg);
		}
	}

	if (err)
		return 4;

	return 0;
}