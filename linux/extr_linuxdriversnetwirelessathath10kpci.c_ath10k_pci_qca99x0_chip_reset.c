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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_pci_cold_reset (struct ath10k*) ; 
 int ath10k_pci_wait_for_target_init (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_pci_qca99x0_chip_reset(struct ath10k *ar)
{
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca99x0 chip reset\n");

	ret = ath10k_pci_cold_reset(ar);
	if (ret) {
		ath10k_warn(ar, "failed to cold reset: %d\n", ret);
		return ret;
	}

	ret = ath10k_pci_wait_for_target_init(ar);
	if (ret) {
		ath10k_warn(ar, "failed to wait for target after cold reset: %d\n",
			    ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca99x0 chip reset complete (cold)\n");

	return 0;
}