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
struct pci_dev {int dummy; } ;
struct iwl_trans {scalar_t__ runtime_pm_mode; int /*<<< orphan*/  drv; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IWL_PLAT_PM_MODE_DISABLED ; 
 int /*<<< orphan*/  iwl_drv_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_free (struct iwl_trans*) ; 
 struct iwl_trans* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_pci_remove(struct pci_dev *pdev)
{
	struct iwl_trans *trans = pci_get_drvdata(pdev);

	/* if RTPM was in use, restore it to the state before probe */
	if (trans->runtime_pm_mode != IWL_PLAT_PM_MODE_DISABLED) {
		/* We should not call forbid here, but we do for now.
		 * Check the comment to pm_runtime_allow() in
		 * iwl_pci_probe().
		 */
		pm_runtime_forbid(trans->dev);
	}

	iwl_drv_stop(trans->drv);

	iwl_trans_pcie_free(trans);
}