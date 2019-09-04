#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fw_warm_reset_counter; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_pci_init_pipes (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_disable (struct ath10k*) ; 
 int ath10k_pci_wait_for_target_init (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_warm_reset_ce (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_warm_reset_clear_lf (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_warm_reset_cpu (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_warm_reset_si0 (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_pci_warm_reset(struct ath10k *ar)
{
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot warm reset\n");

	spin_lock_bh(&ar->data_lock);
	ar->stats.fw_warm_reset_counter++;
	spin_unlock_bh(&ar->data_lock);

	ath10k_pci_irq_disable(ar);

	/* Make sure the target CPU is not doing anything dangerous, e.g. if it
	 * were to access copy engine while host performs copy engine reset
	 * then it is possible for the device to confuse pci-e controller to
	 * the point of bringing host system to a complete stop (i.e. hang).
	 */
	ath10k_pci_warm_reset_si0(ar);
	ath10k_pci_warm_reset_cpu(ar);
	ath10k_pci_init_pipes(ar);
	ath10k_pci_wait_for_target_init(ar);

	ath10k_pci_warm_reset_clear_lf(ar);
	ath10k_pci_warm_reset_ce(ar);
	ath10k_pci_warm_reset_cpu(ar);
	ath10k_pci_init_pipes(ar);

	ret = ath10k_pci_wait_for_target_init(ar);
	if (ret) {
		ath10k_warn(ar, "failed to wait for target init: %d\n", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot warm reset complete\n");

	return 0;
}