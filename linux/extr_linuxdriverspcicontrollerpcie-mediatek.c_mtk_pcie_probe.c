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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pci_host_bridge {int dummy; } ;
struct mtk_pcie {int /*<<< orphan*/  ports; int /*<<< orphan*/  soc; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pci_host_bridge* devm_pci_alloc_host_bridge (struct device*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_pcie_put_resources (struct mtk_pcie*) ; 
 int mtk_pcie_register_host (struct pci_host_bridge*) ; 
 int mtk_pcie_request_resources (struct mtk_pcie*) ; 
 int mtk_pcie_setup (struct mtk_pcie*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 struct mtk_pcie* pci_host_bridge_priv (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_pcie*) ; 

__attribute__((used)) static int mtk_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_pcie *pcie;
	struct pci_host_bridge *host;
	int err;

	host = devm_pci_alloc_host_bridge(dev, sizeof(*pcie));
	if (!host)
		return -ENOMEM;

	pcie = pci_host_bridge_priv(host);

	pcie->dev = dev;
	pcie->soc = of_device_get_match_data(dev);
	platform_set_drvdata(pdev, pcie);
	INIT_LIST_HEAD(&pcie->ports);

	err = mtk_pcie_setup(pcie);
	if (err)
		return err;

	err = mtk_pcie_request_resources(pcie);
	if (err)
		goto put_resources;

	err = mtk_pcie_register_host(host);
	if (err)
		goto put_resources;

	return 0;

put_resources:
	if (!list_empty(&pcie->ports))
		mtk_pcie_put_resources(pcie);

	return err;
}