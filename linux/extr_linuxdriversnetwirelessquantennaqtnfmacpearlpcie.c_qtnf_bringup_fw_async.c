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
struct qtnf_pcie_bus_priv {struct pci_dev* pdev; } ;
struct qtnf_bus {int /*<<< orphan*/  fw_work; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_fw_work_handler ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_bringup_fw_async(struct qtnf_bus *bus)
{
	struct qtnf_pcie_bus_priv *priv = (void *)get_bus_priv(bus);
	struct pci_dev *pdev = priv->pdev;

	get_device(&pdev->dev);
	INIT_WORK(&bus->fw_work, qtnf_fw_work_handler);
	schedule_work(&bus->fw_work);
}