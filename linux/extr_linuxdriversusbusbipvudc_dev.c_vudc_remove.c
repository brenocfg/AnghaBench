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
struct vudc {int /*<<< orphan*/  gadget; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_vudc_hw (struct vudc*) ; 
 int /*<<< orphan*/  kfree (struct vudc*) ; 
 struct vudc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vudc_attr_group ; 

int vudc_remove(struct platform_device *pdev)
{
	struct vudc *udc = platform_get_drvdata(pdev);

	sysfs_remove_group(&pdev->dev.kobj, &vudc_attr_group);
	usb_del_gadget_udc(&udc->gadget);
	cleanup_vudc_hw(udc);
	kfree(udc);
	return 0;
}