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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct wl12xx_vif {scalar_t__ encryption_type; } ;
struct wl1271_station {int /*<<< orphan*/  total_freed_pkts; } ;
struct wl1271 {int /*<<< orphan*/  flags; TYPE_1__* links; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_freed_pkts; } ;

/* Variables and functions */
 scalar_t__ KEY_GEM ; 
 int /*<<< orphan*/  WL1271_FLAG_RECOVERY_IN_PROGRESS ; 
 scalar_t__ WL1271_TX_SQN_POST_RECOVERY_PADDING ; 
 scalar_t__ WL1271_TX_SQN_POST_RECOVERY_PADDING_GEM ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wlcore_save_freed_pkts(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				   u8 hlid, struct ieee80211_sta *sta)
{
	struct wl1271_station *wl_sta;
	u32 sqn_recovery_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING;

	wl_sta = (void *)sta->drv_priv;
	wl_sta->total_freed_pkts = wl->links[hlid].total_freed_pkts;

	/*
	 * increment the initial seq number on recovery to account for
	 * transmitted packets that we haven't yet got in the FW status
	 */
	if (wlvif->encryption_type == KEY_GEM)
		sqn_recovery_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING_GEM;

	if (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		wl_sta->total_freed_pkts += sqn_recovery_padding;
}