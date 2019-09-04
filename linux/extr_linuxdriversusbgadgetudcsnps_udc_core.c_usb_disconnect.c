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
struct udc {scalar_t__ connected; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disconnect_tasklet ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_mask_unused_interrupts (struct udc*) ; 

__attribute__((used)) static void usb_disconnect(struct udc *dev)
{
	/* Return if already disconnected */
	if (!dev->connected)
		return;

	dev_info(dev->dev, "USB Disconnect\n");

	dev->connected = 0;

	/* mask interrupts */
	udc_mask_unused_interrupts(dev);

	/* REVISIT there doesn't seem to be a point to having this
	 * talk to a tasklet ... do it directly, we already hold
	 * the spinlock needed to process the disconnect.
	 */

	tasklet_schedule(&disconnect_tasklet);
}