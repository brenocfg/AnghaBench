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
struct mtu3 {int /*<<< orphan*/  g; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void mtu3_gadget_cleanup(struct mtu3 *mtu)
{
	usb_del_gadget_udc(&mtu->g);
}