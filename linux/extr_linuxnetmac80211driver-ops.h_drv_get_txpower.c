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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_txpower ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  trace_drv_get_txpower (struct ieee80211_local*,struct ieee80211_sub_if_data*,int,int) ; 

__attribute__((used)) static inline int drv_get_txpower(struct ieee80211_local *local,
				  struct ieee80211_sub_if_data *sdata, int *dbm)
{
	int ret;

	if (!local->ops->get_txpower)
		return -EOPNOTSUPP;

	ret = local->ops->get_txpower(&local->hw, &sdata->vif, dbm);
	trace_drv_get_txpower(local, sdata, *dbm, ret);

	return ret;
}