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
struct iwl_beacon_filter_cmd {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
iwl_mvm_beacon_filter_debugfs_parameters(struct ieee80211_vif *vif,
					 struct iwl_beacon_filter_cmd *cmd)
{}