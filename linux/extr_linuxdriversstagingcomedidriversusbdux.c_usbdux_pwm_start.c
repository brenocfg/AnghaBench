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
struct usbdux_private {int pwm_cmd_running; int /*<<< orphan*/  mut; int /*<<< orphan*/  pwm_buf_sz; TYPE_1__* pwm_urb; int /*<<< orphan*/  pwm_delay; int /*<<< orphan*/ * dux_commands; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbdux_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBDUX_CMD_PWM_ON ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_dux_commands (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int usbduxsub_submit_pwm_urbs (struct comedi_device*) ; 

__attribute__((used)) static int usbdux_pwm_start(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct usbdux_private *devpriv = dev->private;
	int ret = 0;

	mutex_lock(&devpriv->mut);

	if (devpriv->pwm_cmd_running)
		goto pwm_start_exit;

	devpriv->dux_commands[1] = devpriv->pwm_delay;
	ret = send_dux_commands(dev, USBDUX_CMD_PWM_ON);
	if (ret < 0)
		goto pwm_start_exit;

	/* initialise the buffer */
	memset(devpriv->pwm_urb->transfer_buffer, 0, devpriv->pwm_buf_sz);

	devpriv->pwm_cmd_running = 1;
	ret = usbduxsub_submit_pwm_urbs(dev);
	if (ret < 0)
		devpriv->pwm_cmd_running = 0;

pwm_start_exit:
	mutex_unlock(&devpriv->mut);

	return ret;
}