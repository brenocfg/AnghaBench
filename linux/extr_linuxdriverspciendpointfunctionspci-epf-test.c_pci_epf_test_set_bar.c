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
struct pci_epf_test {int test_reg_bar; int /*<<< orphan*/ * reg; } ;
struct pci_epf_bar {int flags; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;
struct pci_epf {int /*<<< orphan*/  func_no; struct pci_epf_bar* bar; struct device dev; struct pci_epc* epc; } ;
struct pci_epc {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int BAR_5 ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_32 ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 int pci_epc_set_bar (struct pci_epc*,int /*<<< orphan*/ ,struct pci_epf_bar*) ; 
 int /*<<< orphan*/  pci_epf_free_space (struct pci_epf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_epf_test_set_bar(struct pci_epf *epf)
{
	int bar;
	int ret;
	struct pci_epf_bar *epf_bar;
	struct pci_epc *epc = epf->epc;
	struct device *dev = &epf->dev;
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	enum pci_barno test_reg_bar = epf_test->test_reg_bar;

	for (bar = BAR_0; bar <= BAR_5; bar++) {
		epf_bar = &epf->bar[bar];

		epf_bar->flags |= upper_32_bits(epf_bar->size) ?
			PCI_BASE_ADDRESS_MEM_TYPE_64 :
			PCI_BASE_ADDRESS_MEM_TYPE_32;

		ret = pci_epc_set_bar(epc, epf->func_no, epf_bar);
		if (ret) {
			pci_epf_free_space(epf, epf_test->reg[bar], bar);
			dev_err(dev, "Failed to set BAR%d\n", bar);
			if (bar == test_reg_bar)
				return ret;
		}
		/*
		 * pci_epc_set_bar() sets PCI_BASE_ADDRESS_MEM_TYPE_64
		 * if the specific implementation required a 64-bit BAR,
		 * even if we only requested a 32-bit BAR.
		 */
		if (epf_bar->flags & PCI_BASE_ADDRESS_MEM_TYPE_64)
			bar++;
	}

	return 0;
}