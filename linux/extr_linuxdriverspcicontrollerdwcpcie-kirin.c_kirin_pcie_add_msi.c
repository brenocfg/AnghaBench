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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int msi_irq; } ;
struct dw_pcie {TYPE_1__ pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_pcie_add_msi(struct dw_pcie *pci,
				struct platform_device *pdev)
{
	int irq;

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		irq = platform_get_irq(pdev, 0);
		if (irq < 0) {
			dev_err(&pdev->dev,
				"failed to get MSI IRQ (%d)\n", irq);
			return irq;
		}

		pci->pp.msi_irq = irq;
	}

	return 0;
}