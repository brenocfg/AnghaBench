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
typedef  int /*<<< orphan*/  u32 ;
struct sta_info {TYPE_1__* mesh; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ plink_state; int /*<<< orphan*/  plink_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_MESH_POWER_UNKNOWN ; 
 scalar_t__ NL80211_PLINK_BLOCKED ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int /*<<< orphan*/  ieee80211_mps_set_sta_local_pm (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mps_sta_status_update (struct sta_info*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_plink_dec_estab_count (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static u32 __mesh_plink_deactivate(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	u32 changed = 0;

	lockdep_assert_held(&sta->mesh->plink_lock);

	if (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		changed = mesh_plink_dec_estab_count(sdata);
	sta->mesh->plink_state = NL80211_PLINK_BLOCKED;

	ieee80211_mps_sta_status_update(sta);
	changed |= ieee80211_mps_set_sta_local_pm(sta,
			NL80211_MESH_POWER_UNKNOWN);

	return changed;
}