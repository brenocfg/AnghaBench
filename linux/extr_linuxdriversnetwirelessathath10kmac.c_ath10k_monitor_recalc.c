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
struct ath10k {int monitor_started; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int EPERM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int ath10k_mac_monitor_vdev_is_allowed (struct ath10k*) ; 
 int ath10k_mac_monitor_vdev_is_needed (struct ath10k*) ; 
 int ath10k_monitor_start (struct ath10k*) ; 
 int ath10k_monitor_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_monitor_recalc(struct ath10k *ar)
{
	bool needed;
	bool allowed;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	needed = ath10k_mac_monitor_vdev_is_needed(ar);
	allowed = ath10k_mac_monitor_vdev_is_allowed(ar);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac monitor recalc started? %d needed? %d allowed? %d\n",
		   ar->monitor_started, needed, allowed);

	if (WARN_ON(needed && !allowed)) {
		if (ar->monitor_started) {
			ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor stopping disallowed monitor\n");

			ret = ath10k_monitor_stop(ar);
			if (ret)
				ath10k_warn(ar, "failed to stop disallowed monitor: %d\n",
					    ret);
				/* not serious */
		}

		return -EPERM;
	}

	if (needed == ar->monitor_started)
		return 0;

	if (needed)
		return ath10k_monitor_start(ar);
	else
		return ath10k_monitor_stop(ar);
}