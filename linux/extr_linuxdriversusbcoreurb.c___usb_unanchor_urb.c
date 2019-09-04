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
struct usb_anchor {int /*<<< orphan*/  wait; } ;
struct urb {int /*<<< orphan*/  anchor_list; int /*<<< orphan*/ * anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_anchor_check_wakeup (struct usb_anchor*) ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __usb_unanchor_urb(struct urb *urb, struct usb_anchor *anchor)
{
	urb->anchor = NULL;
	list_del(&urb->anchor_list);
	usb_put_urb(urb);
	if (usb_anchor_check_wakeup(anchor))
		wake_up(&anchor->wait);
}