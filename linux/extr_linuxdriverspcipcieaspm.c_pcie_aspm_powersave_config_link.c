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
struct pcie_link_state {int dummy; } ;
struct pci_dev {struct pcie_link_state* link_state; } ;

/* Variables and functions */
 scalar_t__ POLICY_POWERSAVE ; 
 scalar_t__ POLICY_POWER_SUPERSAVE ; 
 scalar_t__ aspm_disabled ; 
 int /*<<< orphan*/  aspm_lock ; 
 scalar_t__ aspm_policy ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pcie_config_aspm_path (struct pcie_link_state*) ; 
 int /*<<< orphan*/  pcie_set_clkpm (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_to_clkpm_state (struct pcie_link_state*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void pcie_aspm_powersave_config_link(struct pci_dev *pdev)
{
	struct pcie_link_state *link = pdev->link_state;

	if (aspm_disabled || !link)
		return;

	if (aspm_policy != POLICY_POWERSAVE &&
	    aspm_policy != POLICY_POWER_SUPERSAVE)
		return;

	down_read(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	pcie_config_aspm_path(link);
	pcie_set_clkpm(link, policy_to_clkpm_state(link));
	mutex_unlock(&aspm_lock);
	up_read(&pci_bus_sem);
}