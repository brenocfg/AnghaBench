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
typedef  int u16 ;
struct TYPE_2__ {int pci_pm; int debug_sleep_level_override; int /*<<< orphan*/  sleep_cmd; } ;
struct il_priv {TYPE_1__ power_data; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPM_L0S ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
il_power_initialize(struct il_priv *il)
{
	u16 lctl;

	pcie_capability_read_word(il->pci_dev, PCI_EXP_LNKCTL, &lctl);
	il->power_data.pci_pm = !(lctl & PCI_EXP_LNKCTL_ASPM_L0S);

	il->power_data.debug_sleep_level_override = -1;

	memset(&il->power_data.sleep_cmd, 0, sizeof(il->power_data.sleep_cmd));
}