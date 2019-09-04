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
struct usb_gadget {int dummy; } ;
struct mtu3 {int is_self_powered; } ;

/* Variables and functions */
 struct mtu3* gadget_to_mtu3 (struct usb_gadget*) ; 

__attribute__((used)) static int mtu3_gadget_set_self_powered(struct usb_gadget *gadget,
		int is_selfpowered)
{
	struct mtu3 *mtu = gadget_to_mtu3(gadget);

	mtu->is_self_powered = !!is_selfpowered;
	return 0;
}