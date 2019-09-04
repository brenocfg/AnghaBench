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
struct usb_anchor {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 struct urb* usb_get_from_anchor (struct usb_anchor*) ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

void usb_unlink_anchored_urbs(struct usb_anchor *anchor)
{
	struct urb *victim;

	while ((victim = usb_get_from_anchor(anchor)) != NULL) {
		usb_unlink_urb(victim);
		usb_put_urb(victim);
	}
}