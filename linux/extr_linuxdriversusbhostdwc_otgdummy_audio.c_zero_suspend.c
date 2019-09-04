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
struct zero_dev {int /*<<< orphan*/  resume; } ;
struct usb_gadget {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct zero_dev*,char*,...) ; 
 int HZ ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int autoresume ; 
 struct zero_dev* get_gadget_data (struct usb_gadget*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
zero_suspend (struct usb_gadget *gadget)
{
	struct zero_dev		*dev = get_gadget_data (gadget);

	if (gadget->speed == USB_SPEED_UNKNOWN)
		return;

	if (autoresume) {
		mod_timer (&dev->resume, jiffies + (HZ * autoresume));
		DBG (dev, "suspend, wakeup in %d seconds\n", autoresume);
	} else
		DBG (dev, "suspend\n");
}