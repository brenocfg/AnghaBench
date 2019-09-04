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
struct TYPE_4__ {int type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  wdev; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct ieee80211_local {TYPE_1__* ops; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_3__ {int /*<<< orphan*/  change_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EBUSY ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_OCB 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int drv_change_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*,int,int) ; 
 int ieee80211_check_concurrent_iface (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_check_queues (struct ieee80211_sub_if_data*,int) ; 
 int ieee80211_do_open (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_do_stop (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_setup_sdata (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_teardown_sdata (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_type_p2p (TYPE_2__*) ; 

__attribute__((used)) static int ieee80211_runtime_change_iftype(struct ieee80211_sub_if_data *sdata,
					   enum nl80211_iftype type)
{
	struct ieee80211_local *local = sdata->local;
	int ret, err;
	enum nl80211_iftype internal_type = type;
	bool p2p = false;

	ASSERT_RTNL();

	if (!local->ops->change_interface)
		return -EBUSY;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_OCB:
		/*
		 * Could maybe also all others here?
		 * Just not sure how that interacts
		 * with the RX/config path e.g. for
		 * mesh.
		 */
		break;
	default:
		return -EBUSY;
	}

	switch (type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_OCB:
		/*
		 * Could probably support everything
		 * but WDS here (WDS do_open can fail
		 * under memory pressure, which this
		 * code isn't prepared to handle).
		 */
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		p2p = true;
		internal_type = NL80211_IFTYPE_STATION;
		break;
	case NL80211_IFTYPE_P2P_GO:
		p2p = true;
		internal_type = NL80211_IFTYPE_AP;
		break;
	default:
		return -EBUSY;
	}

	ret = ieee80211_check_concurrent_iface(sdata, internal_type);
	if (ret)
		return ret;

	ieee80211_do_stop(sdata, false);

	ieee80211_teardown_sdata(sdata);

	ret = drv_change_interface(local, sdata, internal_type, p2p);
	if (ret)
		type = ieee80211_vif_type_p2p(&sdata->vif);

	/*
	 * Ignore return value here, there's not much we can do since
	 * the driver changed the interface type internally already.
	 * The warnings will hopefully make driver authors fix it :-)
	 */
	ieee80211_check_queues(sdata, type);

	ieee80211_setup_sdata(sdata, type);

	err = ieee80211_do_open(&sdata->wdev, false);
	WARN(err, "type change: do_open returned %d", err);

	return ret;
}