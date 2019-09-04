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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct mac80211_qos_map {int /*<<< orphan*/  qos_map; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  qos_map; } ;
struct cfg80211_qos_map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct mac80211_qos_map*,int /*<<< orphan*/ ) ; 
 struct mac80211_qos_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cfg80211_qos_map*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct mac80211_qos_map*) ; 
 int /*<<< orphan*/  rcu_head ; 
 struct mac80211_qos_map* sdata_dereference (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static int ieee80211_set_qos_map(struct wiphy *wiphy,
				 struct net_device *dev,
				 struct cfg80211_qos_map *qos_map)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct mac80211_qos_map *new_qos_map, *old_qos_map;

	if (qos_map) {
		new_qos_map = kzalloc(sizeof(*new_qos_map), GFP_KERNEL);
		if (!new_qos_map)
			return -ENOMEM;
		memcpy(&new_qos_map->qos_map, qos_map, sizeof(*qos_map));
	} else {
		/* A NULL qos_map was passed to disable QoS mapping */
		new_qos_map = NULL;
	}

	old_qos_map = sdata_dereference(sdata->qos_map, sdata);
	rcu_assign_pointer(sdata->qos_map, new_qos_map);
	if (old_qos_map)
		kfree_rcu(old_qos_map, rcu_head);

	return 0;
}