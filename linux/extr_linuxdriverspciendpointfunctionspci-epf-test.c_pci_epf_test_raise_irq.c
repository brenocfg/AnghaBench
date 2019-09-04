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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_epf_test_reg {int /*<<< orphan*/  status; } ;
struct pci_epf_test {int test_reg_bar; struct pci_epf_test_reg** reg; struct pci_epf* epf; } ;
struct device {int dummy; } ;
struct pci_epf {int /*<<< orphan*/  func_no; struct pci_epc* epc; struct device dev; } ;
struct pci_epc {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
#define  IRQ_TYPE_LEGACY 130 
#define  IRQ_TYPE_MSI 129 
#define  IRQ_TYPE_MSIX 128 
 int /*<<< orphan*/  PCI_EPC_IRQ_LEGACY ; 
 int /*<<< orphan*/  PCI_EPC_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_EPC_IRQ_MSIX ; 
 int /*<<< orphan*/  STATUS_IRQ_RAISED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  pci_epc_raise_irq (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_epf_test_raise_irq(struct pci_epf_test *epf_test, u8 irq_type,
				   u16 irq)
{
	struct pci_epf *epf = epf_test->epf;
	struct device *dev = &epf->dev;
	struct pci_epc *epc = epf->epc;
	enum pci_barno test_reg_bar = epf_test->test_reg_bar;
	struct pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	reg->status |= STATUS_IRQ_RAISED;

	switch (irq_type) {
	case IRQ_TYPE_LEGACY:
		pci_epc_raise_irq(epc, epf->func_no, PCI_EPC_IRQ_LEGACY, 0);
		break;
	case IRQ_TYPE_MSI:
		pci_epc_raise_irq(epc, epf->func_no, PCI_EPC_IRQ_MSI, irq);
		break;
	case IRQ_TYPE_MSIX:
		pci_epc_raise_irq(epc, epf->func_no, PCI_EPC_IRQ_MSIX, irq);
		break;
	default:
		dev_err(dev, "Failed to raise IRQ, unknown type\n");
		break;
	}
}