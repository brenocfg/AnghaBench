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
struct usb_host_endpoint {struct ep_device* ep_dev; } ;
struct ep_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

void usb_remove_ep_devs(struct usb_host_endpoint *endpoint)
{
	struct ep_device *ep_dev = endpoint->ep_dev;

	if (ep_dev) {
		device_unregister(&ep_dev->dev);
		endpoint->ep_dev = NULL;
	}
}