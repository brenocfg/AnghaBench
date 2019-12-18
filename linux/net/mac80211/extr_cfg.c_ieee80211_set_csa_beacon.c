#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_14__ {TYPE_4__* chan; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {TYPE_5__ chandef; int /*<<< orphan*/  ibss_joined; } ;
struct TYPE_16__ {int type; TYPE_6__ bss_conf; } ;
struct ieee80211_if_mesh {int pre_value; int /*<<< orphan*/  csa_role; } ;
struct TYPE_18__ {TYPE_8__* chan; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {TYPE_9__ chandef; } ;
struct TYPE_10__ {int /*<<< orphan*/  next_beacon; } ;
struct TYPE_12__ {struct ieee80211_if_mesh mesh; TYPE_2__ ibss; TYPE_1__ ap; } ;
struct ieee80211_sub_if_data {TYPE_7__ vif; TYPE_3__ u; } ;
struct ieee80211_csa_settings {int count; int /*<<< orphan*/  n_counter_offsets_presp; int /*<<< orphan*/  n_counter_offsets_beacon; int /*<<< orphan*/  counter_offsets_presp; int /*<<< orphan*/  counter_offsets_beacon; } ;
struct cfg80211_csa_settings {int count; TYPE_9__ chandef; int /*<<< orphan*/  beacon_csa; int /*<<< orphan*/  n_counter_offsets_presp; int /*<<< orphan*/  n_counter_offsets_beacon; int /*<<< orphan*/  counter_offsets_presp; int /*<<< orphan*/  counter_offsets_beacon; int /*<<< orphan*/  beacon_after; } ;
struct TYPE_17__ {int /*<<< orphan*/  band; } ;
struct TYPE_13__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_MAX_CSA_COUNTERS_NUM ; 
 int /*<<< orphan*/  IEEE80211_MESH_CSA_ROLE_INIT ; 
 int /*<<< orphan*/  IEEE80211_MESH_CSA_ROLE_NONE ; 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_20 134 
#define  NL80211_CHAN_WIDTH_20_NOHT 133 
#define  NL80211_CHAN_WIDTH_40 132 
#define  NL80211_CHAN_WIDTH_5 131 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MESH_POINT 128 
 int /*<<< orphan*/  cfg80211_beacon_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_get_chandef_type (TYPE_9__*) ; 
 int ieee80211_assign_beacon (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,struct ieee80211_csa_settings*) ; 
 int ieee80211_ibss_csa_beacon (struct ieee80211_sub_if_data*,struct cfg80211_csa_settings*) ; 
 int ieee80211_mesh_csa_beacon (struct ieee80211_sub_if_data*,struct cfg80211_csa_settings*) ; 
 int /*<<< orphan*/  ieee80211_send_action_csa (struct ieee80211_sub_if_data*,struct cfg80211_csa_settings*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_set_csa_beacon(struct ieee80211_sub_if_data *sdata,
				    struct cfg80211_csa_settings *params,
				    u32 *changed)
{
	struct ieee80211_csa_settings csa = {};
	int err;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		sdata->u.ap.next_beacon =
			cfg80211_beacon_dup(&params->beacon_after);
		if (!sdata->u.ap.next_beacon)
			return -ENOMEM;

		/*
		 * With a count of 0, we don't have to wait for any
		 * TBTT before switching, so complete the CSA
		 * immediately.  In theory, with a count == 1 we
		 * should delay the switch until just before the next
		 * TBTT, but that would complicate things so we switch
		 * immediately too.  If we would delay the switch
		 * until the next TBTT, we would have to set the probe
		 * response here.
		 *
		 * TODO: A channel switch with count <= 1 without
		 * sending a CSA action frame is kind of useless,
		 * because the clients won't know we're changing
		 * channels.  The action frame must be implemented
		 * either here or in the userspace.
		 */
		if (params->count <= 1)
			break;

		if ((params->n_counter_offsets_beacon >
		     IEEE80211_MAX_CSA_COUNTERS_NUM) ||
		    (params->n_counter_offsets_presp >
		     IEEE80211_MAX_CSA_COUNTERS_NUM))
			return -EINVAL;

		csa.counter_offsets_beacon = params->counter_offsets_beacon;
		csa.counter_offsets_presp = params->counter_offsets_presp;
		csa.n_counter_offsets_beacon = params->n_counter_offsets_beacon;
		csa.n_counter_offsets_presp = params->n_counter_offsets_presp;
		csa.count = params->count;

		err = ieee80211_assign_beacon(sdata, &params->beacon_csa, &csa);
		if (err < 0) {
			kfree(sdata->u.ap.next_beacon);
			return err;
		}
		*changed |= err;

		break;
	case NL80211_IFTYPE_ADHOC:
		if (!sdata->vif.bss_conf.ibss_joined)
			return -EINVAL;

		if (params->chandef.width != sdata->u.ibss.chandef.width)
			return -EINVAL;

		switch (params->chandef.width) {
		case NL80211_CHAN_WIDTH_40:
			if (cfg80211_get_chandef_type(&params->chandef) !=
			    cfg80211_get_chandef_type(&sdata->u.ibss.chandef))
				return -EINVAL;
		case NL80211_CHAN_WIDTH_5:
		case NL80211_CHAN_WIDTH_10:
		case NL80211_CHAN_WIDTH_20_NOHT:
		case NL80211_CHAN_WIDTH_20:
			break;
		default:
			return -EINVAL;
		}

		/* changes into another band are not supported */
		if (sdata->u.ibss.chandef.chan->band !=
		    params->chandef.chan->band)
			return -EINVAL;

		/* see comments in the NL80211_IFTYPE_AP block */
		if (params->count > 1) {
			err = ieee80211_ibss_csa_beacon(sdata, params);
			if (err < 0)
				return err;
			*changed |= err;
		}

		ieee80211_send_action_csa(sdata, params);

		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT: {
		struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

		if (params->chandef.width != sdata->vif.bss_conf.chandef.width)
			return -EINVAL;

		/* changes into another band are not supported */
		if (sdata->vif.bss_conf.chandef.chan->band !=
		    params->chandef.chan->band)
			return -EINVAL;

		if (ifmsh->csa_role == IEEE80211_MESH_CSA_ROLE_NONE) {
			ifmsh->csa_role = IEEE80211_MESH_CSA_ROLE_INIT;
			if (!ifmsh->pre_value)
				ifmsh->pre_value = 1;
			else
				ifmsh->pre_value++;
		}

		/* see comments in the NL80211_IFTYPE_AP block */
		if (params->count > 1) {
			err = ieee80211_mesh_csa_beacon(sdata, params);
			if (err < 0) {
				ifmsh->csa_role = IEEE80211_MESH_CSA_ROLE_NONE;
				return err;
			}
			*changed |= err;
		}

		if (ifmsh->csa_role == IEEE80211_MESH_CSA_ROLE_INIT)
			ieee80211_send_action_csa(sdata, params);

		break;
		}
#endif
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}