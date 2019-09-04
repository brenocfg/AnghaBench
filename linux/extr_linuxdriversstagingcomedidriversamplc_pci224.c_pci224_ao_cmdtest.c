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
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; unsigned int start_arg; int scan_begin_arg; unsigned int chanlist_len; unsigned int convert_arg; unsigned int scan_end_arg; int stop_arg; scalar_t__ chanlist; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* COMBINE (int,int /*<<< orphan*/ ,int) ; 
 unsigned int CONVERT_PERIOD ; 
 int CR_EDGE ; 
 int CR_FLAGS_MASK ; 
 int CR_INVERT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_SCAN_PERIOD ; 
 unsigned int MIN_SCAN_PERIOD ; 
#define  TRIG_COUNT 132 
#define  TRIG_EXT 131 
#define  TRIG_INT 130 
#define  TRIG_NONE 129 
 int TRIG_NOW ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_min (int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 int pci224_ao_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

__attribute__((used)) static int
pci224_ao_cmdtest(struct comedi_device *dev, struct comedi_subdevice *s,
		  struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_EXT | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_EXT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/*
	 * There's only one external trigger signal (which makes these
	 * tests easier).  Only one thing can use it.
	 */
	arg = 0;
	if (cmd->start_src & TRIG_EXT)
		arg++;
	if (cmd->scan_begin_src & TRIG_EXT)
		arg++;
	if (cmd->stop_src & TRIG_EXT)
		arg++;
	if (arg > 1)
		err |= -EINVAL;

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	switch (cmd->start_src) {
	case TRIG_INT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		break;
	case TRIG_EXT:
		/* Force to external trigger 0. */
		if (cmd->start_arg & ~CR_FLAGS_MASK) {
			cmd->start_arg =
			    COMBINE(cmd->start_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		}
		/* The only flag allowed is CR_EDGE, which is ignored. */
		if (cmd->start_arg & CR_FLAGS_MASK & ~CR_EDGE) {
			cmd->start_arg = COMBINE(cmd->start_arg, 0,
						 CR_FLAGS_MASK & ~CR_EDGE);
			err |= -EINVAL;
		}
		break;
	}

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    MAX_SCAN_PERIOD);

		arg = cmd->chanlist_len * CONVERT_PERIOD;
		if (arg < MIN_SCAN_PERIOD)
			arg = MIN_SCAN_PERIOD;
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);
		break;
	case TRIG_EXT:
		/* Force to external trigger 0. */
		if (cmd->scan_begin_arg & ~CR_FLAGS_MASK) {
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		}
		/* Only allow flags CR_EDGE and CR_INVERT.  Ignore CR_EDGE. */
		if (cmd->scan_begin_arg & CR_FLAGS_MASK &
		    ~(CR_EDGE | CR_INVERT)) {
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0,
				    CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT));
			err |= -EINVAL;
		}
		break;
	}

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	switch (cmd->stop_src) {
	case TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		break;
	case TRIG_EXT:
		/* Force to external trigger 0. */
		if (cmd->stop_arg & ~CR_FLAGS_MASK) {
			cmd->stop_arg =
			    COMBINE(cmd->stop_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		}
		/* The only flag allowed is CR_EDGE, which is ignored. */
		if (cmd->stop_arg & CR_FLAGS_MASK & ~CR_EDGE) {
			cmd->stop_arg =
			    COMBINE(cmd->stop_arg, 0, CR_FLAGS_MASK & ~CR_EDGE);
		}
		break;
	case TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		break;
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments. */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->scan_begin_arg;
		/* Use two timers. */
		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci224_ao_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}