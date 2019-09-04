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
struct ath10k_pci {int ps_awake; int /*<<< orphan*/  ps_lock; scalar_t__ mem; scalar_t__ pci_ps; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_LOCAL_BASE_ADDRESS ; 
 scalar_t__ PCIE_SOC_WAKE_ADDRESS ; 
 int /*<<< orphan*/  PCIE_SOC_WAKE_V_MASK ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int ath10k_pci_wake_wait (struct ath10k*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ath10k_pci_force_wake(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	unsigned long flags;
	int ret = 0;

	if (ar_pci->pci_ps)
		return ret;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	if (!ar_pci->ps_awake) {
		iowrite32(PCIE_SOC_WAKE_V_MASK,
			  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
			  PCIE_SOC_WAKE_ADDRESS);

		ret = ath10k_pci_wake_wait(ar);
		if (ret == 0)
			ar_pci->ps_awake = true;
	}

	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);

	return ret;
}