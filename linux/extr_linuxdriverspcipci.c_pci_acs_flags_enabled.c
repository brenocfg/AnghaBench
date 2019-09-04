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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_ACS_CAP ; 
 scalar_t__ PCI_ACS_CTRL ; 
 int PCI_ACS_EC ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ACS ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static bool pci_acs_flags_enabled(struct pci_dev *pdev, u16 acs_flags)
{
	int pos;
	u16 cap, ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ACS);
	if (!pos)
		return false;

	/*
	 * Except for egress control, capabilities are either required
	 * or only required if controllable.  Features missing from the
	 * capability field can therefore be assumed as hard-wired enabled.
	 */
	pci_read_config_word(pdev, pos + PCI_ACS_CAP, &cap);
	acs_flags &= (cap | PCI_ACS_EC);

	pci_read_config_word(pdev, pos + PCI_ACS_CTRL, &ctrl);
	return (ctrl & acs_flags) == acs_flags;
}