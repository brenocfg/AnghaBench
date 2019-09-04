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
struct urb {int dummy; } ;
struct atusb {int /*<<< orphan*/  idle_urbs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atusb_free_urbs (struct atusb*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atusb_alloc_urbs(struct atusb *atusb, int n)
{
	struct urb *urb;

	while (n) {
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			atusb_free_urbs(atusb);
			return -ENOMEM;
		}
		usb_anchor_urb(urb, &atusb->idle_urbs);
		n--;
	}
	return 0;
}