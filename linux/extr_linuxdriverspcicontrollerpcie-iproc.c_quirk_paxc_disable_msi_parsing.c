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
struct pci_dev {scalar_t__ hdr_type; int /*<<< orphan*/  bus; } ;
struct iproc_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 struct iproc_pcie* iproc_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pcie_paxc_v2_msi_steer (struct iproc_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void quirk_paxc_disable_msi_parsing(struct pci_dev *pdev)
{
	struct iproc_pcie *pcie = iproc_data(pdev->bus);

	if (pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE)
		iproc_pcie_paxc_v2_msi_steer(pcie, 0, false);
}