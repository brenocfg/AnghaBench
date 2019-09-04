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
struct ssb_hcd_device {struct platform_device* ehci_dev; struct platform_device* ohci_dev; } ;
struct ssb_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  ssb_device_disable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 struct ssb_hcd_device* ssb_get_drvdata (struct ssb_device*) ; 

__attribute__((used)) static void ssb_hcd_remove(struct ssb_device *dev)
{
	struct ssb_hcd_device *usb_dev = ssb_get_drvdata(dev);
	struct platform_device *ohci_dev = usb_dev->ohci_dev;
	struct platform_device *ehci_dev = usb_dev->ehci_dev;

	if (ohci_dev)
		platform_device_unregister(ohci_dev);
	if (ehci_dev)
		platform_device_unregister(ehci_dev);

	ssb_device_disable(dev, 0);
}