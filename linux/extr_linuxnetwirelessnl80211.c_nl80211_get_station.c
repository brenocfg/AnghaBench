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
typedef  int /*<<< orphan*/  u8 ;
struct station_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  sinfo ;
struct TYPE_2__ {int /*<<< orphan*/  get_station; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_STATION ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  cfg80211_sinfo_release_content (struct station_info*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  memset (struct station_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nl80211_send_station (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,struct net_device*,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_get_station (struct net_device*,struct net_device*,int /*<<< orphan*/ *,struct station_info*) ; 

__attribute__((used)) static int nl80211_get_station(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct station_info sinfo;
	struct sk_buff *msg;
	u8 *mac_addr = NULL;
	int err;

	memset(&sinfo, 0, sizeof(sinfo));

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (!rdev->ops->get_station)
		return -EOPNOTSUPP;

	err = rdev_get_station(rdev, dev, mac_addr, &sinfo);
	if (err)
		return err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		cfg80211_sinfo_release_content(&sinfo);
		return -ENOMEM;
	}

	if (nl80211_send_station(msg, NL80211_CMD_NEW_STATION,
				 info->snd_portid, info->snd_seq, 0,
				 rdev, dev, mac_addr, &sinfo) < 0) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	return genlmsg_reply(msg, info);
}