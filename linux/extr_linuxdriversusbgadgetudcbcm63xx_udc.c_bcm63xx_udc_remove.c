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
struct platform_device {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  driver; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm63xx_udc_cleanup_debugfs (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_uninit_udc_hw (struct bcm63xx_udc*) ; 
 struct bcm63xx_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm63xx_udc_remove(struct platform_device *pdev)
{
	struct bcm63xx_udc *udc = platform_get_drvdata(pdev);

	bcm63xx_udc_cleanup_debugfs(udc);
	usb_del_gadget_udc(&udc->gadget);
	BUG_ON(udc->driver);

	bcm63xx_uninit_udc_hw(udc);

	return 0;
}