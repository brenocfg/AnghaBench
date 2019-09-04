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
struct usbduxsigma_private {int ao_timer; int ao_counter; int ao_cmd_running; int /*<<< orphan*/  mut; int /*<<< orphan*/  n_ao_urbs; int /*<<< orphan*/  ao_urbs; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;
struct comedi_cmd {int scan_begin_arg; scalar_t__ start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usbduxsigma_ao_inttrig ; 
 int usbduxsigma_submit_urbs (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsigma_ao_cmd(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct usbduxsigma_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int ret;

	mutex_lock(&devpriv->mut);

	/*
	 * For now, only "scan" timing is supported.  A future version may
	 * support "convert" timing in high speed mode.
	 *
	 * Timing of the scan: every 1ms all channels updated at once.
	 */
	devpriv->ao_timer = cmd->scan_begin_arg / 1000000;

	devpriv->ao_counter = devpriv->ao_timer;

	if (cmd->start_src == TRIG_NOW) {
		/* enable this acquisition operation */
		devpriv->ao_cmd_running = 1;
		ret = usbduxsigma_submit_urbs(dev, devpriv->ao_urbs,
					      devpriv->n_ao_urbs, 0);
		if (ret < 0) {
			devpriv->ao_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			return ret;
		}
		s->async->inttrig = NULL;
	} else {	/* TRIG_INT */
		s->async->inttrig = usbduxsigma_ao_inttrig;
	}

	mutex_unlock(&devpriv->mut);

	return 0;
}