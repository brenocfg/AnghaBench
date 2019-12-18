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
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_vif_copy_chanctx_to_vlans (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_vif_copy_chanctx_to_vlans(struct ieee80211_sub_if_data *sdata,
					 bool clear)
{
	struct ieee80211_local *local = sdata->local;

	mutex_lock(&local->chanctx_mtx);

	__ieee80211_vif_copy_chanctx_to_vlans(sdata, clear);

	mutex_unlock(&local->chanctx_mtx);
}