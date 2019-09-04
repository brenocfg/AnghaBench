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
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  kevent; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

void usbnet_defer_kevent (struct usbnet *dev, int work)
{
	set_bit (work, &dev->flags);
	if (!schedule_work (&dev->kevent))
		netdev_dbg(dev->net, "kevent %d may have been dropped\n", work);
	else
		netdev_dbg(dev->net, "kevent %d scheduled\n", work);
}