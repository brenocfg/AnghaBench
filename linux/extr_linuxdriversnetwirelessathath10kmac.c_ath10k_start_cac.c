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
struct ath10k {int /*<<< orphan*/  monitor_vdev_id; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CAC_RUNNING ; 
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ath10k_monitor_recalc (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_start_cac(struct ath10k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	set_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);

	ret = ath10k_monitor_recalc(ar);
	if (ret) {
		ath10k_warn(ar, "failed to start monitor (cac): %d\n", ret);
		clear_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac cac start monitor vdev %d\n",
		   ar->monitor_vdev_id);

	return 0;
}