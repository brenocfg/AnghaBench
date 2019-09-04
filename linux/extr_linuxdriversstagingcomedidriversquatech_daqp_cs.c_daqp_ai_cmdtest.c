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
struct daqp_private {void* pacer_div; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct daqp_private* private; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; unsigned int start_arg; unsigned int chanlist_len; unsigned int scan_end_arg; unsigned int scan_begin_arg; unsigned int convert_arg; unsigned int stop_arg; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DAQP_MAX_TIMER_SPEED ; 
 int EINVAL ; 
 int TRIG_COUNT ; 
 int TRIG_FOLLOW ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (unsigned int*,int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 void* daqp_ns_to_timer (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daqp_ai_cmdtest(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_cmd *cmd)
{
	struct daqp_private *devpriv = dev->private;
	int err = 0;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/* the async command requires a pacer */
	if (cmd->scan_begin_src != TRIG_TIMER && cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->scan_begin_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    DAQP_MAX_TIMER_SPEED);

	if (cmd->convert_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    DAQP_MAX_TIMER_SPEED);

		if (cmd->scan_begin_src == TRIG_TIMER) {
			/*
			 * If both scan_begin and convert are both timer
			 * values, the only way that can make sense is if
			 * the scan time is the number of conversions times
			 * the convert time.
			 */
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg,
							   arg);
		}
	}

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg, 0x00ffffff);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		arg = cmd->convert_arg;
		devpriv->pacer_div = daqp_ns_to_timer(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	} else if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->scan_begin_arg;
		devpriv->pacer_div = daqp_ns_to_timer(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (err)
		return 4;

	return 0;
}