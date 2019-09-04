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
struct rockchip_pcie {struct device* dev; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rockchip_pcie*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct rockchip_pcie*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  rockchip_pcie_client_irq_handler ; 
 int /*<<< orphan*/  rockchip_pcie_legacy_int_handler ; 
 int /*<<< orphan*/  rockchip_pcie_subsys_irq_handler ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int rockchip_pcie_setup_irq(struct rockchip_pcie *rockchip)
{
	int irq, err;
	struct device *dev = rockchip->dev;
	struct platform_device *pdev = to_platform_device(dev);

	irq = platform_get_irq_byname(pdev, "sys");
	if (irq < 0) {
		dev_err(dev, "missing sys IRQ resource\n");
		return irq;
	}

	err = devm_request_irq(dev, irq, rockchip_pcie_subsys_irq_handler,
			       IRQF_SHARED, "pcie-sys", rockchip);
	if (err) {
		dev_err(dev, "failed to request PCIe subsystem IRQ\n");
		return err;
	}

	irq = platform_get_irq_byname(pdev, "legacy");
	if (irq < 0) {
		dev_err(dev, "missing legacy IRQ resource\n");
		return irq;
	}

	irq_set_chained_handler_and_data(irq,
					 rockchip_pcie_legacy_int_handler,
					 rockchip);

	irq = platform_get_irq_byname(pdev, "client");
	if (irq < 0) {
		dev_err(dev, "missing client IRQ resource\n");
		return irq;
	}

	err = devm_request_irq(dev, irq, rockchip_pcie_client_irq_handler,
			       IRQF_SHARED, "pcie-client", rockchip);
	if (err) {
		dev_err(dev, "failed to request PCIe client IRQ\n");
		return err;
	}

	return 0;
}