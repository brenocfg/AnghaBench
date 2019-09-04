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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct kirin_pcie {void* sysctrl; void* crgctrl; TYPE_1__* pci; void* phy_base; void* apb_base; } ;
struct TYPE_2__ {void* dbi_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 long PTR_ERR (void*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 void* syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static long kirin_pcie_get_resource(struct kirin_pcie *kirin_pcie,
				    struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *apb;
	struct resource *phy;
	struct resource *dbi;

	apb = platform_get_resource_byname(pdev, IORESOURCE_MEM, "apb");
	kirin_pcie->apb_base = devm_ioremap_resource(dev, apb);
	if (IS_ERR(kirin_pcie->apb_base))
		return PTR_ERR(kirin_pcie->apb_base);

	phy = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	kirin_pcie->phy_base = devm_ioremap_resource(dev, phy);
	if (IS_ERR(kirin_pcie->phy_base))
		return PTR_ERR(kirin_pcie->phy_base);

	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	kirin_pcie->pci->dbi_base = devm_ioremap_resource(dev, dbi);
	if (IS_ERR(kirin_pcie->pci->dbi_base))
		return PTR_ERR(kirin_pcie->pci->dbi_base);

	kirin_pcie->crgctrl =
		syscon_regmap_lookup_by_compatible("hisilicon,hi3660-crgctrl");
	if (IS_ERR(kirin_pcie->crgctrl))
		return PTR_ERR(kirin_pcie->crgctrl);

	kirin_pcie->sysctrl =
		syscon_regmap_lookup_by_compatible("hisilicon,hi3660-sctrl");
	if (IS_ERR(kirin_pcie->sysctrl))
		return PTR_ERR(kirin_pcie->sysctrl);

	return 0;
}