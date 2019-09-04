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
struct usbduxfast_private {int /*<<< orphan*/  mut; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbduxfast_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usbduxfast_ai_stop (struct comedi_device*,int) ; 

__attribute__((used)) static int usbduxfast_ai_cancel(struct comedi_device *dev,
				struct comedi_subdevice *s)
{
	struct usbduxfast_private *devpriv = dev->private;
	int ret;

	mutex_lock(&devpriv->mut);
	ret = usbduxfast_ai_stop(dev, 1);
	mutex_unlock(&devpriv->mut);

	return ret;
}