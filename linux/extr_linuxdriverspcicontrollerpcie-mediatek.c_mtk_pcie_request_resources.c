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
struct list_head {int dummy; } ;
struct pci_host_bridge {struct list_head windows; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  io; } ;
struct mtk_pcie {TYPE_2__ io; int /*<<< orphan*/  pio; int /*<<< orphan*/  busn; TYPE_1__ offset; int /*<<< orphan*/  mem; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_pci_remap_iospace (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_request_pci_bus_resources (struct device*,struct list_head*) ; 
 int /*<<< orphan*/  pci_add_resource (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_resource_offset (struct list_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_host_bridge* pci_host_bridge_from_priv (struct mtk_pcie*) ; 

__attribute__((used)) static int mtk_pcie_request_resources(struct mtk_pcie *pcie)
{
	struct pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	struct list_head *windows = &host->windows;
	struct device *dev = pcie->dev;
	int err;

	pci_add_resource_offset(windows, &pcie->pio, pcie->offset.io);
	pci_add_resource_offset(windows, &pcie->mem, pcie->offset.mem);
	pci_add_resource(windows, &pcie->busn);

	err = devm_request_pci_bus_resources(dev, windows);
	if (err < 0)
		return err;

	devm_pci_remap_iospace(dev, &pcie->pio, pcie->io.start);

	return 0;
}