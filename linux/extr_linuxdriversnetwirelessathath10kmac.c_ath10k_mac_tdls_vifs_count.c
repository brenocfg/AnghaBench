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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ath10k_mac_tdls_vifs_count_iter ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ath10k_mac_tdls_vifs_count(struct ieee80211_hw *hw)
{
	int num_tdls_vifs = 0;

	ieee80211_iterate_active_interfaces_atomic(hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath10k_mac_tdls_vifs_count_iter,
						   &num_tdls_vifs);
	return num_tdls_vifs;
}