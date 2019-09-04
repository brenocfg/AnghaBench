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
struct iwl_trans_pcie {TYPE_1__* pci_dev; } ;
struct iwl_trans {int dummy; } ;
struct TYPE_4__ {scalar_t__ d0i3_disable; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 TYPE_2__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_trans_pcie_unref(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	if (iwlwifi_mod_params.d0i3_disable)
		return;

	pm_runtime_mark_last_busy(&trans_pcie->pci_dev->dev);
	pm_runtime_put_autosuspend(&trans_pcie->pci_dev->dev);

#ifdef CONFIG_PM
	IWL_DEBUG_RPM(trans, "runtime usage count: %d\n",
		      atomic_read(&trans_pcie->pci_dev->dev.power.usage_count));
#endif /* CONFIG_PM */
}