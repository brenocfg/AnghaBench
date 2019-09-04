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
struct pci_dev {TYPE_1__* sriov; struct pci_dev* physfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  hdr_type; int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_VENDOR_ID ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_read_vf_config_common(struct pci_dev *virtfn)
{
	struct pci_dev *physfn = virtfn->physfn;

	/*
	 * Some config registers are the same across all associated VFs.
	 * Read them once from VF0 so we can skip reading them from the
	 * other VFs.
	 *
	 * PCIe r4.0, sec 9.3.4.1, technically doesn't require all VFs to
	 * have the same Revision ID and Subsystem ID, but we assume they
	 * do.
	 */
	pci_read_config_dword(virtfn, PCI_CLASS_REVISION,
			      &physfn->sriov->class);
	pci_read_config_byte(virtfn, PCI_HEADER_TYPE,
			     &physfn->sriov->hdr_type);
	pci_read_config_word(virtfn, PCI_SUBSYSTEM_VENDOR_ID,
			     &physfn->sriov->subsystem_vendor);
	pci_read_config_word(virtfn, PCI_SUBSYSTEM_ID,
			     &physfn->sriov->subsystem_device);
}