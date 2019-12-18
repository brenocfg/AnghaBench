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
struct usX2Ydev {int /*<<< orphan*/  In04urb; int /*<<< orphan*/  In04Buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  In04WaitQueue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i_usX2Y_In04Int ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usX2Ydev*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_urb_ep_type_check (int /*<<< orphan*/ ) ; 

int usX2Y_In04_init(struct usX2Ydev *usX2Y)
{
	if (! (usX2Y->In04urb = usb_alloc_urb(0, GFP_KERNEL)))
		return -ENOMEM;

	if (! (usX2Y->In04Buf = kmalloc(21, GFP_KERNEL)))
		return -ENOMEM;
	 
	init_waitqueue_head(&usX2Y->In04WaitQueue);
	usb_fill_int_urb(usX2Y->In04urb, usX2Y->dev, usb_rcvintpipe(usX2Y->dev, 0x4),
			 usX2Y->In04Buf, 21,
			 i_usX2Y_In04Int, usX2Y,
			 10);
	if (usb_urb_ep_type_check(usX2Y->In04urb))
		return -EINVAL;
	return usb_submit_urb(usX2Y->In04urb, GFP_KERNEL);
}