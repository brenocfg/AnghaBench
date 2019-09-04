#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  chandef; } ;
struct TYPE_7__ {TYPE_4__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; TYPE_2__* local; } ;
struct TYPE_5__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int cfg80211_chandef_dfs_required (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_radar_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_mesh_csa_mark_radar(struct ieee80211_sub_if_data *sdata)
{
	int err;

	/* if the current channel is a DFS channel, mark the channel as
	 * unavailable.
	 */
	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &sdata->vif.bss_conf.chandef,
					    NL80211_IFTYPE_MESH_POINT);
	if (err > 0)
		cfg80211_radar_event(sdata->local->hw.wiphy,
				     &sdata->vif.bss_conf.chandef, GFP_ATOMIC);
}