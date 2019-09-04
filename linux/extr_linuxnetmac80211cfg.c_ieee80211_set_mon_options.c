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
typedef  int u32 ;
struct vif_params {int flags; scalar_t__ vht_mumimo_follow_addr; scalar_t__ vht_mumimo_groups; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ mntr; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  monitor_sdata; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int MONITOR_FLAG_ACTIVE ; 
 int MONITOR_FLAG_COOK_FRAMES ; 
 int /*<<< orphan*/  ieee80211_adjust_monitor_flags (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_configure_filter (struct ieee80211_local*) ; 
 scalar_t__ ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_set_mu_mimo_follow (struct ieee80211_sub_if_data*,struct vif_params*) ; 
 struct ieee80211_sub_if_data* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_set_mon_options(struct ieee80211_sub_if_data *sdata,
				     struct vif_params *params)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_sub_if_data *monitor_sdata;

	/* check flags first */
	if (params->flags && ieee80211_sdata_running(sdata)) {
		u32 mask = MONITOR_FLAG_COOK_FRAMES | MONITOR_FLAG_ACTIVE;

		/*
		 * Prohibit MONITOR_FLAG_COOK_FRAMES and
		 * MONITOR_FLAG_ACTIVE to be changed while the
		 * interface is up.
		 * Else we would need to add a lot of cruft
		 * to update everything:
		 *	cooked_mntrs, monitor and all fif_* counters
		 *	reconfigure hardware
		 */
		if ((params->flags & mask) != (sdata->u.mntr.flags & mask))
			return -EBUSY;
	}

	/* also validate MU-MIMO change */
	monitor_sdata = rtnl_dereference(local->monitor_sdata);

	if (!monitor_sdata &&
	    (params->vht_mumimo_groups || params->vht_mumimo_follow_addr))
		return -EOPNOTSUPP;

	/* apply all changes now - no failures allowed */

	if (monitor_sdata)
		ieee80211_set_mu_mimo_follow(monitor_sdata, params);

	if (params->flags) {
		if (ieee80211_sdata_running(sdata)) {
			ieee80211_adjust_monitor_flags(sdata, -1);
			sdata->u.mntr.flags = params->flags;
			ieee80211_adjust_monitor_flags(sdata, 1);

			ieee80211_configure_filter(local);
		} else {
			/*
			 * Because the interface is down, ieee80211_do_stop
			 * and ieee80211_do_open take care of "everything"
			 * mentioned in the comment above.
			 */
			sdata->u.mntr.flags = params->flags;
		}
	}

	return 0;
}