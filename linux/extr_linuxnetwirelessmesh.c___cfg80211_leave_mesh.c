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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  chandef; scalar_t__ beacon_interval; scalar_t__ mesh_id_len; scalar_t__ conn_owner_nlportid; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  leave_mesh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  cfg80211_sched_dfs_chan_update (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rdev_leave_mesh (struct cfg80211_registered_device*,struct net_device*) ; 
 int /*<<< orphan*/  rdev_set_qos_map (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *) ; 

int __cfg80211_leave_mesh(struct cfg80211_registered_device *rdev,
			  struct net_device *dev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_MESH_POINT)
		return -EOPNOTSUPP;

	if (!rdev->ops->leave_mesh)
		return -EOPNOTSUPP;

	if (!wdev->mesh_id_len)
		return -ENOTCONN;

	err = rdev_leave_mesh(rdev, dev);
	if (!err) {
		wdev->conn_owner_nlportid = 0;
		wdev->mesh_id_len = 0;
		wdev->beacon_interval = 0;
		memset(&wdev->chandef, 0, sizeof(wdev->chandef));
		rdev_set_qos_map(rdev, dev, NULL);
		cfg80211_sched_dfs_chan_update(rdev);
	}

	return err;
}