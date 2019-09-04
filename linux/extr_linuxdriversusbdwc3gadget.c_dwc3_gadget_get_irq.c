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
struct dwc3 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_gadget_get_irq(struct dwc3 *dwc)
{
	struct platform_device *dwc3_pdev = to_platform_device(dwc->dev);
	int irq;

	irq = platform_get_irq_byname(dwc3_pdev, "peripheral");
	if (irq > 0)
		goto out;

	if (irq == -EPROBE_DEFER)
		goto out;

	irq = platform_get_irq_byname(dwc3_pdev, "dwc_usb3");
	if (irq > 0)
		goto out;

	if (irq == -EPROBE_DEFER)
		goto out;

	irq = platform_get_irq(dwc3_pdev, 0);
	if (irq > 0)
		goto out;

	if (irq != -EPROBE_DEFER)
		dev_err(dwc->dev, "missing peripheral IRQ\n");

	if (!irq)
		irq = -EINVAL;

out:
	return irq;
}