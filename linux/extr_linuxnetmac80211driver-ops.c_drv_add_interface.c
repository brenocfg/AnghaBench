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
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ mntr; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  flags; TYPE_4__ vif; TYPE_2__ u; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_3__* ops; } ;
struct TYPE_7__ {int (* add_interface ) (int /*<<< orphan*/ *,TYPE_4__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_SDATA_IN_DRIVER ; 
 int MONITOR_FLAG_ACTIVE ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  WANT_MONITOR_VIF ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  trace_drv_add_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 

int drv_add_interface(struct ieee80211_local *local,
		      struct ieee80211_sub_if_data *sdata)
{
	int ret;

	might_sleep();

	if (WARN_ON(sdata->vif.type == NL80211_IFTYPE_AP_VLAN ||
		    (sdata->vif.type == NL80211_IFTYPE_MONITOR &&
		     !ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF) &&
		     !(sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE))))
		return -EINVAL;

	trace_drv_add_interface(local, sdata);
	ret = local->ops->add_interface(&local->hw, &sdata->vif);
	trace_drv_return_int(local, ret);

	if (ret == 0)
		sdata->flags |= IEEE80211_SDATA_IN_DRIVER;

	return ret;
}