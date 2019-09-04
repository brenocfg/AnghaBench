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
struct zero_dev {int /*<<< orphan*/  resume; scalar_t__ req; } ;
struct usb_gadget {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct zero_dev*,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ep_req (int /*<<< orphan*/ ,scalar_t__) ; 
 struct zero_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  kfree (struct zero_dev*) ; 
 int /*<<< orphan*/  set_gadget_data (struct usb_gadget*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zero_unbind (struct usb_gadget *gadget)
{
	struct zero_dev		*dev = get_gadget_data (gadget);

	DBG (dev, "unbind\n");

	/* we've already been disconnected ... no i/o is active */
	if (dev->req)
		free_ep_req (gadget->ep0, dev->req);
	del_timer_sync (&dev->resume);
	kfree (dev);
	set_gadget_data (gadget, NULL);
}