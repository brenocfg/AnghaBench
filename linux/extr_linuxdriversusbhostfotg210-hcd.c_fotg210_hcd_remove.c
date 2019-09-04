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
struct usb_hcd {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 struct usb_hcd* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int fotg210_hcd_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb_hcd *hcd = dev_get_drvdata(dev);

	if (!hcd)
		return 0;

	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);

	return 0;
}