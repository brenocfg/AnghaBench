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
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct station_info {int dummy; } ;
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_2__* nlh; int /*<<< orphan*/  skb; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  sinfo ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dump_station; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_STATION ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  memset (struct station_info*,int /*<<< orphan*/ ,int) ; 
 int nl80211_prepare_wdev_dump (struct netlink_callback*,struct cfg80211_registered_device**,struct wireless_dev**) ; 
 scalar_t__ nl80211_send_station (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct station_info*) ; 
 int rdev_dump_station (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int nl80211_dump_station(struct sk_buff *skb,
				struct netlink_callback *cb)
{
	struct station_info sinfo;
	struct cfg80211_registered_device *rdev;
	struct wireless_dev *wdev;
	u8 mac_addr[ETH_ALEN];
	int sta_idx = cb->args[2];
	int err;

	rtnl_lock();
	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	if (err)
		goto out_err;

	if (!wdev->netdev) {
		err = -EINVAL;
		goto out_err;
	}

	if (!rdev->ops->dump_station) {
		err = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		memset(&sinfo, 0, sizeof(sinfo));
		err = rdev_dump_station(rdev, wdev->netdev, sta_idx,
					mac_addr, &sinfo);
		if (err == -ENOENT)
			break;
		if (err)
			goto out_err;

		if (nl80211_send_station(skb, NL80211_CMD_NEW_STATION,
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				rdev, wdev->netdev, mac_addr,
				&sinfo) < 0)
			goto out;

		sta_idx++;
	}

 out:
	cb->args[2] = sta_idx;
	err = skb->len;
 out_err:
	rtnl_unlock();

	return err;
}