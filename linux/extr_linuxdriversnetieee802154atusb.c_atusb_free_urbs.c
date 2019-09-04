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
struct urb {int /*<<< orphan*/  context; } ;
struct atusb {int /*<<< orphan*/  idle_urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atusb_free_urbs(struct atusb *atusb)
{
	struct urb *urb;

	while (1) {
		urb = usb_get_from_anchor(&atusb->idle_urbs);
		if (!urb)
			break;
		kfree_skb(urb->context);
		usb_free_urb(urb);
	}
}