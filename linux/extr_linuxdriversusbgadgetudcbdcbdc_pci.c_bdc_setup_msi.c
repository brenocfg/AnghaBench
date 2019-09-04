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

/* Variables and functions */
 int pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int bdc_setup_msi(struct pci_dev *pci)
{
	int ret;

	ret = pci_enable_msi(pci);
	if (ret) {
		pr_err("failed to allocate MSI entry\n");
		return ret;
	}

	return ret;
}