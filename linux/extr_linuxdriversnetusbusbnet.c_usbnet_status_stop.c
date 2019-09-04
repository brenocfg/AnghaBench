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
struct usbnet {scalar_t__ interrupt_count; int /*<<< orphan*/  interrupt_mutex; TYPE_1__* udev; scalar_t__ interrupt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void usbnet_status_stop(struct usbnet *dev)
{
	if (dev->interrupt) {
		mutex_lock(&dev->interrupt_mutex);
		WARN_ON(dev->interrupt_count == 0);

		if (dev->interrupt_count && --dev->interrupt_count == 0)
			usb_kill_urb(dev->interrupt);

		dev_dbg(&dev->udev->dev,
			"decremented interrupt URB count to %d\n",
			dev->interrupt_count);
		mutex_unlock(&dev->interrupt_mutex);
	}
}