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
struct net2272 {int /*<<< orphan*/  dev; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_registers ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net2272*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
net2272_remove(struct net2272 *dev)
{
	usb_del_gadget_udc(&dev->gadget);
	free_irq(dev->irq, dev);
	iounmap(dev->base_addr);
	device_remove_file(dev->dev, &dev_attr_registers);

	dev_info(dev->dev, "unbind\n");
}