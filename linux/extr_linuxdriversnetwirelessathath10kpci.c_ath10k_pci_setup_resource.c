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
struct ath10k_pci {int /*<<< orphan*/  rx_post_retry; int /*<<< orphan*/  ps_lock; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ QCA_REV_6174 (struct ath10k*) ; 
 scalar_t__ QCA_REV_9377 (struct ath10k*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_pci_alloc_pipes (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_override_ce_config (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_replenish_retry ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_pci_setup_resource(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int ret;

	spin_lock_init(&ce->ce_lock);
	spin_lock_init(&ar_pci->ps_lock);

	timer_setup(&ar_pci->rx_post_retry, ath10k_pci_rx_replenish_retry, 0);

	if (QCA_REV_6174(ar) || QCA_REV_9377(ar))
		ath10k_pci_override_ce_config(ar);

	ret = ath10k_pci_alloc_pipes(ar);
	if (ret) {
		ath10k_err(ar, "failed to allocate copy engine pipes: %d\n",
			   ret);
		return ret;
	}

	return 0;
}