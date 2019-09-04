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
struct zero_dev {TYPE_1__* gadget; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct zero_dev*,char*,int) ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int usb_gadget_wakeup (TYPE_1__*) ; 

__attribute__((used)) static void
zero_autoresume (unsigned long _dev)
{
	struct zero_dev	*dev = (struct zero_dev *) _dev;
	int		status;

	/* normally the host would be woken up for something
	 * more significant than just a timer firing...
	 */
	if (dev->gadget->speed != USB_SPEED_UNKNOWN) {
		status = usb_gadget_wakeup (dev->gadget);
		DBG (dev, "wakeup --> %d\n", status);
	}
}