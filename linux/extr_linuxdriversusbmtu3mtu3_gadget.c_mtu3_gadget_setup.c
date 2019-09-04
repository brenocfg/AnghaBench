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
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ sg_supported; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_speed; int /*<<< orphan*/ * ops; } ;
struct mtu3 {int delayed_status; int /*<<< orphan*/  dev; TYPE_1__ g; scalar_t__ is_active; int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTU3_DRIVER_NAME ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtu3_gadget_init_eps (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_gadget_ops ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ ,TYPE_1__*) ; 

int mtu3_gadget_setup(struct mtu3 *mtu)
{
	int ret;

	mtu->g.ops = &mtu3_gadget_ops;
	mtu->g.max_speed = mtu->max_speed;
	mtu->g.speed = USB_SPEED_UNKNOWN;
	mtu->g.sg_supported = 0;
	mtu->g.name = MTU3_DRIVER_NAME;
	mtu->is_active = 0;
	mtu->delayed_status = false;

	mtu3_gadget_init_eps(mtu);

	ret = usb_add_gadget_udc(mtu->dev, &mtu->g);
	if (ret)
		dev_err(mtu->dev, "failed to register udc\n");

	return ret;
}