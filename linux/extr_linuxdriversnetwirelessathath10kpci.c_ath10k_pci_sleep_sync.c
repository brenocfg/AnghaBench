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
struct ath10k_pci {scalar_t__ pci_ps; scalar_t__ ps_wake_refcount; int /*<<< orphan*/  ps_lock; int /*<<< orphan*/  ps_timer; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ath10k_pci_sleep (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_force_sleep (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath10k_pci_sleep_sync(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	unsigned long flags;

	if (ar_pci->pci_ps == 0) {
		ath10k_pci_force_sleep(ar);
		return;
	}

	del_timer_sync(&ar_pci->ps_timer);

	spin_lock_irqsave(&ar_pci->ps_lock, flags);
	WARN_ON(ar_pci->ps_wake_refcount > 0);
	__ath10k_pci_sleep(ar);
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
}