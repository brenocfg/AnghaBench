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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct intel_xhci_usb_data {int /*<<< orphan*/  role_sw; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_xhci_usb_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_xhci_usb_data*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sw_desc ; 
 int /*<<< orphan*/  usb_role_switch_register (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_xhci_usb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct intel_xhci_usb_data *data;
	struct resource *res;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;
	data->base = devm_ioremap_nocache(dev, res->start, resource_size(res));
	if (!data->base)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);

	data->role_sw = usb_role_switch_register(dev, &sw_desc);
	if (IS_ERR(data->role_sw))
		return PTR_ERR(data->role_sw);

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	return 0;
}