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
struct renesas_usb3 {int /*<<< orphan*/  lock; scalar_t__ start_to_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb3_connect (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_mode_by_role_sw (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_vbus_out (struct renesas_usb3*,int) ; 

__attribute__((used)) static void usb3_mode_config(struct renesas_usb3 *usb3, bool host, bool a_dev)
{
	unsigned long flags;

	spin_lock_irqsave(&usb3->lock, flags);
	usb3_set_mode_by_role_sw(usb3, host);
	usb3_vbus_out(usb3, a_dev);
	/* for A-Peripheral or forced B-device mode */
	if ((!host && a_dev) || usb3->start_to_connect)
		usb3_connect(usb3);
	spin_unlock_irqrestore(&usb3->lock, flags);
}