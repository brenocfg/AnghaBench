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
struct ath5k_vif_iter_data {int any_assoc; int need_set_hw_addr; int found_active; int /*<<< orphan*/ * hw_macaddr; } ;
struct ath5k_hw {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ath5k_vif_iter ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath5k_vif_iter_data*) ; 

bool
ath5k_any_vif_assoc(struct ath5k_hw *ah)
{
	struct ath5k_vif_iter_data iter_data;
	iter_data.hw_macaddr = NULL;
	iter_data.any_assoc = false;
	iter_data.need_set_hw_addr = false;
	iter_data.found_active = true;

	ieee80211_iterate_active_interfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath5k_vif_iter, &iter_data);
	return iter_data.any_assoc;
}