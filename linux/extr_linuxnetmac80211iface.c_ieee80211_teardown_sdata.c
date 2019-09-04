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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; scalar_t__ fragment_next; TYPE_1__* fragments; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb_list; } ;

/* Variables and functions */
 int IEEE80211_FRAGMENT_MAX ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_debugfs_remove_netdev (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_free_keys (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_mesh_teardown_sdata (struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_vif_is_mesh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_teardown_sdata(struct ieee80211_sub_if_data *sdata)
{
	int i;

	/* free extra data */
	ieee80211_free_keys(sdata, false);

	ieee80211_debugfs_remove_netdev(sdata);

	for (i = 0; i < IEEE80211_FRAGMENT_MAX; i++)
		__skb_queue_purge(&sdata->fragments[i].skb_list);
	sdata->fragment_next = 0;

	if (ieee80211_vif_is_mesh(&sdata->vif))
		ieee80211_mesh_teardown_sdata(sdata);
}