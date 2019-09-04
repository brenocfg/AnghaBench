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
struct das1800_board {int ai_speed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct das1800_board* board_ptr; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; int start_arg; scalar_t__ stop_arg; scalar_t__ convert_arg; scalar_t__ chanlist_len; int scan_end_arg; scalar_t__ chanlist; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TRIG_COUNT 129 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
#define  TRIG_NONE 128 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (int*,scalar_t__) ; 
 int comedi_check_trigger_arg_min (scalar_t__*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 int das1800_ai_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 
 int das1800_ai_fixup_burst_timing (struct comedi_device*,struct comedi_cmd*) ; 
 int das1800_ai_fixup_paced_timing (struct comedi_device*,struct comedi_cmd*) ; 

__attribute__((used)) static int das1800_ai_cmdtest(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_cmd *cmd)
{
	const struct das1800_board *board = dev->board_ptr;
	int err = 0;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_EXT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/* burst scans must use timed conversions */
	if (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	/* the external pin TGIN must use the same polarity */
	if (cmd->start_src == TRIG_EXT && cmd->stop_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->start_arg,
						   cmd->stop_arg);

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	if (cmd->start_arg == TRIG_NOW)
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	if (cmd->convert_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	}

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	switch (cmd->stop_src) {
	case TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		break;
	case TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		break;
	default:
		break;
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->scan_begin_src == TRIG_FOLLOW)
			err |= das1800_ai_fixup_paced_timing(dev, cmd);
		else /* TRIG_TIMER or TRIG_EXT */
			err |= das1800_ai_fixup_burst_timing(dev, cmd);
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das1800_ai_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}