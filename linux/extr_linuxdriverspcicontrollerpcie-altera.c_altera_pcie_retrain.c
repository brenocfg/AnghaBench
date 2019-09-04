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
typedef  int u16 ;
struct altera_pcie {int /*<<< orphan*/  root_bus_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_SLS ; 
 int PCI_EXP_LNKCAP_SLS_2_5GB ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_RL ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_CLS ; 
 int PCI_EXP_LNKSTA_CLS_2_5GB ; 
 int /*<<< orphan*/  RP_DEVFN ; 
 int /*<<< orphan*/  altera_pcie_link_up (struct altera_pcie*) ; 
 int /*<<< orphan*/  altera_read_cap_word (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  altera_wait_link_retrain (struct altera_pcie*) ; 
 int /*<<< orphan*/  altera_write_cap_word (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void altera_pcie_retrain(struct altera_pcie *pcie)
{
	u16 linkcap, linkstat, linkctl;

	if (!altera_pcie_link_up(pcie))
		return;

	/*
	 * Set the retrain bit if the PCIe rootport support > 2.5GB/s, but
	 * current speed is 2.5 GB/s.
	 */
	altera_read_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN, PCI_EXP_LNKCAP,
			     &linkcap);
	if ((linkcap & PCI_EXP_LNKCAP_SLS) <= PCI_EXP_LNKCAP_SLS_2_5GB)
		return;

	altera_read_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN, PCI_EXP_LNKSTA,
			     &linkstat);
	if ((linkstat & PCI_EXP_LNKSTA_CLS) == PCI_EXP_LNKSTA_CLS_2_5GB) {
		altera_read_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				     PCI_EXP_LNKCTL, &linkctl);
		linkctl |= PCI_EXP_LNKCTL_RL;
		altera_write_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				      PCI_EXP_LNKCTL, linkctl);

		altera_wait_link_retrain(pcie);
	}
}