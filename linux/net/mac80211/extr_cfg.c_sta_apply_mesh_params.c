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
typedef  int /*<<< orphan*/  u32 ;
struct station_parameters {int sta_modify_mask; int plink_state; int plink_action; scalar_t__ local_pm; int /*<<< orphan*/  peer_aid; } ;
struct sta_info {TYPE_4__* mesh; struct ieee80211_sub_if_data* sdata; } ;
struct TYPE_5__ {scalar_t__ power_mode; } ;
struct TYPE_6__ {TYPE_1__ mshcfg; } ;
struct TYPE_7__ {TYPE_2__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; } ;
struct ieee80211_local {int dummy; } ;
struct TYPE_8__ {int const plink_state; int /*<<< orphan*/  tx_rate_avg; int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 scalar_t__ NL80211_MESH_POWER_UNKNOWN ; 
#define  NL80211_PLINK_ACTION_BLOCK 137 
#define  NL80211_PLINK_ACTION_NO_ACTION 136 
#define  NL80211_PLINK_ACTION_OPEN 135 
#define  NL80211_PLINK_BLOCKED 134 
#define  NL80211_PLINK_CNF_RCVD 133 
#define  NL80211_PLINK_ESTAB 132 
#define  NL80211_PLINK_HOLDING 131 
#define  NL80211_PLINK_LISTEN 130 
#define  NL80211_PLINK_OPN_RCVD 129 
#define  NL80211_PLINK_OPN_SNT 128 
 int STATION_PARAM_APPLY_PLINK_STATE ; 
 int /*<<< orphan*/  ewma_mesh_tx_rate_avg_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ewma_mesh_tx_rate_avg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_mbss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mps_set_sta_local_pm (struct sta_info*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_mps_sta_status_update (struct sta_info*) ; 
 int /*<<< orphan*/  mesh_plink_block (struct sta_info*) ; 
 int /*<<< orphan*/  mesh_plink_dec_estab_count (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_plink_inc_estab_count (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_plink_open (struct sta_info*) ; 

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

			ewma_mesh_tx_rate_avg_init(&sta->mesh->tx_rate_avg);
			/* init at low value */
			ewma_mesh_tx_rate_avg_add(&sta->mesh->tx_rate_avg, 10);

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