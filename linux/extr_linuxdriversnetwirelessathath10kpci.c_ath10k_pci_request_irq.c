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
struct ath10k_pci {int oper_irq_mode; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
#define  ATH10K_PCI_IRQ_LEGACY 129 
#define  ATH10K_PCI_IRQ_MSI 128 
 int EINVAL ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int ath10k_pci_request_irq_legacy (struct ath10k*) ; 
 int ath10k_pci_request_irq_msi (struct ath10k*) ; 

__attribute__((used)) static int ath10k_pci_request_irq(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	switch (ar_pci->oper_irq_mode) {
	case ATH10K_PCI_IRQ_LEGACY:
		return ath10k_pci_request_irq_legacy(ar);
	case ATH10K_PCI_IRQ_MSI:
		return ath10k_pci_request_irq_msi(ar);
	default:
		return -EINVAL;
	}
}