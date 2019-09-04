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
struct ath10k_pci {scalar_t__ oper_irq_mode; int /*<<< orphan*/  pdev; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATH10K_PCI_IRQ_AUTO ; 
 scalar_t__ ATH10K_PCI_IRQ_LEGACY ; 
 scalar_t__ ATH10K_PCI_IRQ_MSI ; 
 int PCIE_INTR_CE_MASK_ALL ; 
 scalar_t__ PCIE_INTR_ENABLE_ADDRESS ; 
 int PCIE_INTR_FIRMWARE_MASK ; 
 scalar_t__ SOC_CORE_BASE_ADDRESS ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_pci_init_napi (struct ath10k*) ; 
 scalar_t__ ath10k_pci_irq_mode ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,int) ; 
 int pci_enable_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_pci_init_irq(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	int ret;

	ath10k_pci_init_napi(ar);

	if (ath10k_pci_irq_mode != ATH10K_PCI_IRQ_AUTO)
		ath10k_info(ar, "limiting irq mode to: %d\n",
			    ath10k_pci_irq_mode);

	/* Try MSI */
	if (ath10k_pci_irq_mode != ATH10K_PCI_IRQ_LEGACY) {
		ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_MSI;
		ret = pci_enable_msi(ar_pci->pdev);
		if (ret == 0)
			return 0;

		/* fall-through */
	}

	/* Try legacy irq
	 *
	 * A potential race occurs here: The CORE_BASE write
	 * depends on target correctly decoding AXI address but
	 * host won't know when target writes BAR to CORE_CTRL.
	 * This write might get lost if target has NOT written BAR.
	 * For now, fix the race by repeating the write in below
	 * synchronization checking.
	 */
	ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_LEGACY;

	ath10k_pci_write32(ar, SOC_CORE_BASE_ADDRESS + PCIE_INTR_ENABLE_ADDRESS,
			   PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL);

	return 0;
}