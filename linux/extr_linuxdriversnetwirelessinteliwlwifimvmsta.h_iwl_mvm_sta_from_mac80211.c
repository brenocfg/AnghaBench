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
typedef  void iwl_mvm_sta ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct iwl_mvm_sta *
iwl_mvm_sta_from_mac80211(struct ieee80211_sta *sta)
{
	return (void *)sta->drv_priv;
}