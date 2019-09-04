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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct dummy {TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_function ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dummy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (TYPE_1__*) ; 

__attribute__((used)) static int dummy_udc_remove(struct platform_device *pdev)
{
	struct dummy	*dum = platform_get_drvdata(pdev);

	device_remove_file(&dum->gadget.dev, &dev_attr_function);
	usb_del_gadget_udc(&dum->gadget);
	return 0;
}