#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * next_beacon; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;
struct TYPE_4__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MESH_POINT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ieee80211_assign_beacon (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ieee80211_ibss_finish_csa (struct ieee80211_sub_if_data*) ; 
 int ieee80211_mesh_finish_csa (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_set_after_csa_beacon(struct ieee80211_sub_if_data *sdata,
					  u32 *changed)
{
	int err;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		err = ieee80211_assign_beacon(sdata, sdata->u.ap.next_beacon,
					      NULL);
		kfree(sdata->u.ap.next_beacon);
		sdata->u.ap.next_beacon = NULL;

		if (err < 0)
			return err;
		*changed |= err;
		break;
	case NL80211_IFTYPE_ADHOC:
		err = ieee80211_ibss_finish_csa(sdata);
		if (err < 0)
			return err;
		*changed |= err;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		err = ieee80211_mesh_finish_csa(sdata);
		if (err < 0)
			return err;
		*changed |= err;
		break;
#endif
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	return 0;
}