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
struct ath10k_pci {int /*<<< orphan*/  oper_irq_mode; } ;
struct ath10k_ahb {int /*<<< orphan*/  irq; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_PCI_IRQ_LEGACY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ath10k_ahb_interrupt_handler ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ath10k*) ; 

__attribute__((used)) static int ath10k_ahb_request_irq_legacy(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	int ret;

	ret = request_irq(ar_ahb->irq,
			  ath10k_ahb_interrupt_handler,
			  IRQF_SHARED, "ath10k_ahb", ar);
	if (ret) {
		ath10k_warn(ar, "failed to request legacy irq %d: %d\n",
			    ar_ahb->irq, ret);
		return ret;
	}
	ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_LEGACY;

	return 0;
}