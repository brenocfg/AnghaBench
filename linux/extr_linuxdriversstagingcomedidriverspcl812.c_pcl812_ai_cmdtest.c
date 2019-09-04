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
struct pcl812_private {scalar_t__ use_ext_trg; } ;
struct pcl812_board {int ai_ns_min; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  pacer; struct pcl812_private* private; struct pcl812_board* board_ptr; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; unsigned int start_arg; unsigned int scan_begin_arg; unsigned int convert_arg; unsigned int chanlist_len; unsigned int scan_end_arg; unsigned int stop_arg; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int TRIG_COUNT ; 
 unsigned int TRIG_EXT ; 
 unsigned int TRIG_FOLLOW ; 
 unsigned int TRIG_NONE ; 
 unsigned int TRIG_NOW ; 
 unsigned int TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,int) ; 
 int comedi_check_trigger_is_unique (unsigned int) ; 
 int comedi_check_trigger_src (unsigned int*,unsigned int) ; 

__attribute__((used)) static int pcl812_ai_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	const struct pcl812_board *board = dev->board_ptr;
	struct pcl812_private *devpriv = dev->private;
	int err = 0;
	unsigned int flags;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);

	if (devpriv->use_ext_trg)
		flags = TRIG_EXT;
	else
		flags = TRIG_TIMER;
	err |= comedi_check_trigger_src(&cmd->convert_src, flags);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	if (cmd->convert_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_ns_min);
	} else {	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	}

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		unsigned int arg = cmd->convert_arg;

		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	}

	if (err)
		return 4;

	return 0;
}