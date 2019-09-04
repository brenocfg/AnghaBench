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
struct controller {int dummy; } ;

/* Variables and functions */
 struct pci_dev* ctrl_dev (struct controller*) ; 
 int /*<<< orphan*/  pcie_wait_for_link (struct pci_dev*,int) ; 

__attribute__((used)) static void pcie_wait_link_active(struct controller *ctrl)
{
	struct pci_dev *pdev = ctrl_dev(ctrl);

	pcie_wait_for_link(pdev, true);
}