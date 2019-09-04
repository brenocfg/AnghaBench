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
struct usbdux_private {int /*<<< orphan*/  mut; int /*<<< orphan*/  pwm_cmd_running; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBDUX_CMD_PWM_OFF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_dux_commands (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbdux_pwm_stop (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_pwm_cancel(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct usbdux_private *devpriv = dev->private;
	int ret;

	mutex_lock(&devpriv->mut);
	/* unlink only if it is really running */
	usbdux_pwm_stop(dev, devpriv->pwm_cmd_running);
	ret = send_dux_commands(dev, USBDUX_CMD_PWM_OFF);
	mutex_unlock(&devpriv->mut);

	return ret;
}