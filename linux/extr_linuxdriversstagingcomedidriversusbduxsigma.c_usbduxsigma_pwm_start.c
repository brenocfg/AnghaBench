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
struct usbduxsigma_private {int pwm_cmd_running; int /*<<< orphan*/  pwm_buf_sz; TYPE_1__* pwm_urb; int /*<<< orphan*/  pwm_delay; int /*<<< orphan*/ * dux_commands; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBDUXSIGMA_PWM_ON_CMD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbbuxsigma_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int usbduxsigma_submit_pwm_urb (struct comedi_device*) ; 

__attribute__((used)) static int usbduxsigma_pwm_start(struct comedi_device *dev,
				 struct comedi_subdevice *s)
{
	struct usbduxsigma_private *devpriv = dev->private;
	int ret;

	if (devpriv->pwm_cmd_running)
		return 0;

	devpriv->dux_commands[1] = devpriv->pwm_delay;
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_PWM_ON_CMD);
	if (ret < 0)
		return ret;

	memset(devpriv->pwm_urb->transfer_buffer, 0, devpriv->pwm_buf_sz);

	devpriv->pwm_cmd_running = 1;
	ret = usbduxsigma_submit_pwm_urb(dev);
	if (ret < 0) {
		devpriv->pwm_cmd_running = 0;
		return ret;
	}

	return 0;
}