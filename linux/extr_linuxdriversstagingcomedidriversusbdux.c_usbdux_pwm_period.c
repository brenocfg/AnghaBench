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
struct usbdux_private {int pwm_delay; unsigned int pwm_period; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned int MIN_PWM_PERIOD ; 

__attribute__((used)) static int usbdux_pwm_period(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     unsigned int period)
{
	struct usbdux_private *devpriv = dev->private;
	int fx2delay = 255;

	if (period < MIN_PWM_PERIOD)
		return -EAGAIN;

	fx2delay = (period / (6 * 512 * 1000 / 33)) - 6;
	if (fx2delay > 255)
		return -EAGAIN;

	devpriv->pwm_delay = fx2delay;
	devpriv->pwm_period = period;

	return 0;
}