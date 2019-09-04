#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {TYPE_1__* gadget; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_vbus_mach_info {int dummy; } ;
struct TYPE_4__ {struct usb_otg* otg; } ;
struct gpio_vbus_data {int /*<<< orphan*/  work; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 struct gpio_vbus_mach_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vbus_powered (struct gpio_vbus_mach_info*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct gpio_vbus_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t gpio_vbus_irq(int irq, void *data)
{
	struct platform_device *pdev = data;
	struct gpio_vbus_mach_info *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_vbus_data *gpio_vbus = platform_get_drvdata(pdev);
	struct usb_otg *otg = gpio_vbus->phy.otg;

	dev_dbg(&pdev->dev, "VBUS %s (gadget: %s)\n",
		is_vbus_powered(pdata) ? "supplied" : "inactive",
		otg->gadget ? otg->gadget->name : "none");

	if (otg->gadget)
		schedule_delayed_work(&gpio_vbus->work, msecs_to_jiffies(100));

	return IRQ_HANDLED;
}