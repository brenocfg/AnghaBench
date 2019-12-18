#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int plink_timeout; } ;
struct ieee80211_if_mesh {int /*<<< orphan*/  housekeeping_timer; TYPE_2__ mshcfg; } ;
struct TYPE_3__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ IEEE80211_MESH_HOUSEKEEPING_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_mbss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_expire (struct ieee80211_sub_if_data*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mesh_accept_plinks_update (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_path_expire (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 

__attribute__((used)) static void ieee80211_mesh_housekeeping(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 changed;

	if (ifmsh->mshcfg.plink_timeout > 0)
		ieee80211_sta_expire(sdata, ifmsh->mshcfg.plink_timeout * HZ);
	mesh_path_expire(sdata);

	changed = mesh_accept_plinks_update(sdata);
	ieee80211_mbss_info_change_notify(sdata, changed);

	mod_timer(&ifmsh->housekeeping_timer,
		  round_jiffies(jiffies +
				IEEE80211_MESH_HOUSEKEEPING_INTERVAL));
}