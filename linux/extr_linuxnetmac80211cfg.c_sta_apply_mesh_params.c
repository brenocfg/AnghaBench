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
struct station_parameters {int dummy; } ;
struct sta_info {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void sta_apply_mesh_params(struct ieee80211_local *local,
				  struct sta_info *sta,
				  struct station_parameters *params)
{
#ifdef CONFIG_MAC80211_MESH
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	u32 changed = 0;

	if (params->sta_modify_mask & STATION_PARAM_APPLY_PLINK_STATE) {
		switch (params->plink_state) {
		case NL80211_PLINK_ESTAB:
			if (sta->mesh->plink_state != NL80211_PLINK_ESTAB)
				changed = mesh_plink_inc_estab_count(sdata);
			sta->mesh->plink_state = params->plink_state;
			sta->mesh->aid = params->peer_aid;

			ieee80211_mps_sta_status_update(sta);
			changed |= ieee80211_mps_set_sta_local_pm(sta,
				      sdata->u.mesh.mshcfg.power_mode);
			break;
		case NL80211_PLINK_LISTEN:
		case NL80211_PLINK_BLOCKED:
		case NL80211_PLINK_OPN_SNT:
		case NL80211_PLINK_OPN_RCVD:
		case NL80211_PLINK_CNF_RCVD:
		case NL80211_PLINK_HOLDING:
			if (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
				changed = mesh_plink_dec_estab_count(sdata);
			sta->mesh->plink_state = params->plink_state;

			ieee80211_mps_sta_status_update(sta);
			changed |= ieee80211_mps_set_sta_local_pm(sta,
					NL80211_MESH_POWER_UNKNOWN);
			break;
		default:
			/*  nothing  */
			break;
		}
	}

	switch (params->plink_action) {
	case NL80211_PLINK_ACTION_NO_ACTION:
		/* nothing */
		break;
	case NL80211_PLINK_ACTION_OPEN:
		changed |= mesh_plink_open(sta);
		break;
	case NL80211_PLINK_ACTION_BLOCK:
		changed |= mesh_plink_block(sta);
		break;
	}

	if (params->local_pm)
		changed |= ieee80211_mps_set_sta_local_pm(sta,
							  params->local_pm);

	ieee80211_mbss_info_change_notify(sdata, changed);
#endif
}