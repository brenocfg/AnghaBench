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
struct usbduxfast_private {int ai_cmd_running; int /*<<< orphan*/  mut; int /*<<< orphan*/  ignore; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct usbduxfast_private* private; } ;
struct comedi_cmd {int convert_arg; int chanlist_len; scalar_t__ start_src; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 long MIN_SAMPLING_PERIOD ; 
 int /*<<< orphan*/  PACKETS_TO_IGNORE ; 
 int /*<<< orphan*/  SENDADCOMMANDS ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usbduxfast_ai_inttrig ; 
 int /*<<< orphan*/  usbduxfast_cmd_data (struct comedi_device*,int,int,int,unsigned int,int) ; 
 int usbduxfast_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int usbduxfast_submit_urb (struct comedi_device*) ; 

__attribute__((used)) static int usbduxfast_ai_cmd(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct usbduxfast_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int rngmask = 0xff;
	int j, ret;
	long steps, steps_tmp;

	mutex_lock(&devpriv->mut);
	if (devpriv->ai_cmd_running) {
		ret = -EBUSY;
		goto cmd_exit;
	}

	/*
	 * ignore the first buffers from the device if there
	 * is an error condition
	 */
	devpriv->ignore = PACKETS_TO_IGNORE;

	steps = (cmd->convert_arg * 30) / 1000;

	switch (cmd->chanlist_len) {
	case 1:
		/*
		 * one channel
		 */

		if (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		/*
		 * for external trigger: looping in this state until
		 * the RDY0 pin becomes zero
		 */

		/* we loop here until ready has been set */
		if (cmd->start_src == TRIG_EXT) {
			/* branch back to state 0 */
			/* deceision state w/o data */
			/* RDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01, rngmask, 0x00);
		} else {	/* we just proceed to state 1 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x00, rngmask, 0x00);
		}

		if (steps < MIN_SAMPLING_PERIOD) {
			/* for fast single channel aqu without mux */
			if (steps <= 1) {
				/*
				 * we just stay here at state 1 and rexecute
				 * the same state this gives us 30MHz sampling
				 * rate
				 */

				/* branch back to state 1 */
				/* deceision state with data */
				/* doesn't matter */
				usbduxfast_cmd_data(dev, 1,
						    0x89, 0x03, rngmask, 0xff);
			} else {
				/*
				 * we loop through two states: data and delay
				 * max rate is 15MHz
				 */
				/* data */
				/* doesn't matter */
				usbduxfast_cmd_data(dev, 1, steps - 1,
						    0x02, rngmask, 0x00);

				/* branch back to state 1 */
				/* deceision state w/o data */
				/* doesn't matter */
				usbduxfast_cmd_data(dev, 2,
						    0x09, 0x01, rngmask, 0xff);
			}
		} else {
			/*
			 * we loop through 3 states: 2x delay and 1x data
			 * this gives a min sampling rate of 60kHz
			 */

			/* we have 1 state with duration 1 */
			steps = steps - 1;

			/* do the first part of the delay */
			usbduxfast_cmd_data(dev, 1,
					    steps / 2, 0x00, rngmask, 0x00);

			/* and the second part */
			usbduxfast_cmd_data(dev, 2, steps - steps / 2,
					    0x00, rngmask, 0x00);

			/* get the data and branch back */

			/* branch back to state 1 */
			/* deceision state w data */
			/* doesn't matter */
			usbduxfast_cmd_data(dev, 3,
					    0x09, 0x03, rngmask, 0xff);
		}
		break;

	case 2:
		/*
		 * two channels
		 * commit data to the FIFO
		 */

		if (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		/* data */
		usbduxfast_cmd_data(dev, 0, 0x01, 0x02, rngmask, 0x00);

		/* we have 1 state with duration 1: state 0 */
		steps_tmp = steps - 1;

		if (CR_RANGE(cmd->chanlist[1]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		/* do the first part of the delay */
		/* count */
		usbduxfast_cmd_data(dev, 1, steps_tmp / 2,
				    0x00, 0xfe & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 2, steps_tmp  - steps_tmp / 2,
				    0x00, rngmask, 0x00);

		/* data */
		usbduxfast_cmd_data(dev, 3, 0x01, 0x02, rngmask, 0x00);

		/*
		 * we have 2 states with duration 1: step 6 and
		 * the IDLE state
		 */
		steps_tmp = steps - 2;

		if (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		/* do the first part of the delay */
		/* reset */
		usbduxfast_cmd_data(dev, 4, steps_tmp / 2,
				    0x00, (0xff - 0x02) & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 5, steps_tmp - steps_tmp / 2,
				    0x00, rngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);
		break;

	case 3:
		/*
		 * three channels
		 */
		for (j = 0; j < 1; j++) {
			int index = j * 2;

			if (CR_RANGE(cmd->chanlist[j]) > 0)
				rngmask = 0xff - 0x04;
			else
				rngmask = 0xff;
			/*
			 * commit data to the FIFO and do the first part
			 * of the delay
			 */
			/* data */
			/* no change */
			usbduxfast_cmd_data(dev, index, steps / 2,
					    0x02, rngmask, 0x00);

			if (CR_RANGE(cmd->chanlist[j + 1]) > 0)
				rngmask = 0xff - 0x04;
			else
				rngmask = 0xff;

			/* do the second part of the delay */
			/* no data */
			/* count */
			usbduxfast_cmd_data(dev, index + 1, steps - steps / 2,
					    0x00, 0xfe & rngmask, 0x00);
		}

		/* 2 steps with duration 1: the idele step and step 6: */
		steps_tmp = steps - 2;

		/* commit data to the FIFO and do the first part of the delay */
		/* data */
		usbduxfast_cmd_data(dev, 4, steps_tmp / 2,
				    0x02, rngmask, 0x00);

		if (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		/* do the second part of the delay */
		/* no data */
		/* reset */
		usbduxfast_cmd_data(dev, 5, steps_tmp - steps_tmp / 2,
				    0x00, (0xff - 0x02) & rngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);
		break;

	case 16:
		if (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		else
			rngmask = 0xff;

		if (cmd->start_src == TRIG_EXT) {
			/*
			 * we loop here until ready has been set
			 */

			/* branch back to state 0 */
			/* deceision state w/o data */
			/* reset */
			/* RDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01,
					    (0xff - 0x02) & rngmask, 0x00);
		} else {
			/*
			 * we just proceed to state 1
			 */

			/* 30us reset pulse */
			/* reset */
			usbduxfast_cmd_data(dev, 0, 0xff, 0x00,
					    (0xff - 0x02) & rngmask, 0x00);
		}

		/* commit data to the FIFO */
		/* data */
		usbduxfast_cmd_data(dev, 1, 0x01, 0x02, rngmask, 0x00);

		/* we have 2 states with duration 1 */
		steps = steps - 2;

		/* do the first part of the delay */
		usbduxfast_cmd_data(dev, 2, steps / 2,
				    0x00, 0xfe & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 3, steps - steps / 2,
				    0x00, rngmask, 0x00);

		/* branch back to state 1 */
		/* deceision state w/o data */
		/* doesn't matter */
		usbduxfast_cmd_data(dev, 4, 0x09, 0x01, rngmask, 0xff);

		break;
	}

	/* 0 means that the AD commands are sent */
	ret = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	if (ret < 0)
		goto cmd_exit;

	if ((cmd->start_src == TRIG_NOW) || (cmd->start_src == TRIG_EXT)) {
		/* enable this acquisition operation */
		devpriv->ai_cmd_running = 1;
		ret = usbduxfast_submit_urb(dev);
		if (ret < 0) {
			devpriv->ai_cmd_running = 0;
			/* fixme: unlink here?? */
			goto cmd_exit;
		}
		s->async->inttrig = NULL;
	} else {	/* TRIG_INT */
		s->async->inttrig = usbduxfast_ai_inttrig;
	}

cmd_exit:
	mutex_unlock(&devpriv->mut);

	return ret;
}