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
struct usba_udc {int num_ep; int /*<<< orphan*/ * usba_ep; int /*<<< orphan*/  gadget; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usba_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usba_cleanup_debugfs (struct usba_udc*) ; 
 int /*<<< orphan*/  usba_ep_cleanup_debugfs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usba_udc_remove(struct platform_device *pdev)
{
	struct usba_udc *udc;
	int i;

	udc = platform_get_drvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	usb_del_gadget_udc(&udc->gadget);

	for (i = 1; i < udc->num_ep; i++)
		usba_ep_cleanup_debugfs(&udc->usba_ep[i]);
	usba_cleanup_debugfs(udc);

	return 0;
}