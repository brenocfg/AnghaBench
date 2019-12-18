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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  netdev; } ;
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_2__* nlh; int /*<<< orphan*/  skb; } ;
struct mpath_info {int dummy; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dump_mpath; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int nl80211_prepare_wdev_dump (struct netlink_callback*,struct cfg80211_registered_device**,struct wireless_dev**) ; 
 scalar_t__ nl80211_send_mpath (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ; 
 int rdev_dump_mpath (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int nl80211_dump_mpath(struct sk_buff *skb,
			      struct netlink_callback *cb)
{
	struct mpath_info pinfo;
	struct cfg80211_registered_device *rdev;
	struct wireless_dev *wdev;
	u8 dst[ETH_ALEN];
	u8 next_hop[ETH_ALEN];
	int path_idx = cb->args[2];
	int err;

	rtnl_lock();
	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	if (err)
		goto out_err;

	if (!rdev->ops->dump_mpath) {
		err = -EOPNOTSUPP;
		goto out_err;
	}

	if (wdev->iftype != NL80211_IFTYPE_MESH_POINT) {
		err = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		err = rdev_dump_mpath(rdev, wdev->netdev, path_idx, dst,
				      next_hop, &pinfo);
		if (err == -ENOENT)
			break;
		if (err)
			goto out_err;

		if (nl80211_send_mpath(skb, NETLINK_CB(cb->skb).portid,
				       cb->nlh->nlmsg_seq, NLM_F_MULTI,
				       wdev->netdev, dst, next_hop,
				       &pinfo) < 0)
			goto out;

		path_idx++;
	}

 out:
	cb->args[2] = path_idx;
	err = skb->len;
 out_err:
	rtnl_unlock();
	return err;
}