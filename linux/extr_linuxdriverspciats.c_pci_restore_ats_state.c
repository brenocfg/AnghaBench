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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {scalar_t__ ats_cap; scalar_t__ ats_stu; int /*<<< orphan*/  is_virtfn; int /*<<< orphan*/  ats_enabled; } ;

/* Variables and functions */
 scalar_t__ PCI_ATS_CTRL ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_ENABLE ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_STU (scalar_t__) ; 
 scalar_t__ PCI_ATS_MIN_STU ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void pci_restore_ats_state(struct pci_dev *dev)
{
	u16 ctrl;

	if (!dev->ats_enabled)
		return;

	ctrl = PCI_ATS_CTRL_ENABLE;
	if (!dev->is_virtfn)
		ctrl |= PCI_ATS_CTRL_STU(dev->ats_stu - PCI_ATS_MIN_STU);
	pci_write_config_word(dev, dev->ats_cap + PCI_ATS_CTRL, ctrl);
}