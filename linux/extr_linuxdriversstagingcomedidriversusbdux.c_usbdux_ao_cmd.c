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
struct usbdux_private {int ao_cmd_running; int ao_timer; int ao_counter; int /*<<< orphan*/  mut; int /*<<< orphan*/  n_ao_urbs; int /*<<< orphan*/  ao_urbs; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct usbdux_private* private; } ;
struct comedi_cmd {int convert_arg; int scan_begin_arg; scalar_t__ start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usbdux_ao_inttrig ; 
 int usbdux_submit_urbs (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct usbdux_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int ret = -EBUSY;

	mutex_lock(&devpriv->mut);

	if (devpriv->ao_cmd_running)
		goto ao_cmd_exit;

	/* we count in steps of 1ms (125us) */
	/* 125us mode not used yet */
	if (0) {		/* (devpriv->high_speed) */
		/* 125us */
		/* timing of the conversion itself: every 125 us */
		devpriv->ao_timer = cmd->convert_arg / 125000;
	} else {
		/* 1ms */
		/* timing of the scan: we get all channels at once */
		devpriv->ao_timer = cmd->scan_begin_arg / 1000000;
		if (devpriv->ao_timer < 1) {
			ret = -EINVAL;
			goto ao_cmd_exit;
		}
	}

	devpriv->ao_counter = devpriv->ao_timer;

	if (cmd->start_src == TRIG_NOW) {
		/* enable this acquisition operation */
		devpriv->ao_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ao_urbs,
					 devpriv->n_ao_urbs, 0);
		if (ret < 0) {
			devpriv->ao_cmd_running = 0;
			/* fixme: unlink here?? */
			goto ao_cmd_exit;
		}
		s->async->inttrig = NULL;
	} else {
		/* TRIG_INT */
		/* submit the urbs later */
		/* wait for an internal signal */
		s->async->inttrig = usbdux_ao_inttrig;
	}

ao_cmd_exit:
	mutex_unlock(&devpriv->mut);

	return ret;
}