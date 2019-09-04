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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
struct mpath_info {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  pinfo ;
struct TYPE_4__ {scalar_t__ iftype; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_mpath; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NL80211_ATTR_MAC ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  memset (struct mpath_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nl80211_send_mpath (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_get_mpath (struct net_device*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ; 

__attribute__((used)) static int nl80211_get_mpath(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	int err;
	struct net_device *dev = info->user_ptr[1];
	struct mpath_info pinfo;
	struct sk_buff *msg;
	u8 *dst = NULL;
	u8 next_hop[ETH_ALEN];

	memset(&pinfo, 0, sizeof(pinfo));

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	dst = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (!rdev->ops->get_mpath)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_MESH_POINT)
		return -EOPNOTSUPP;

	err = rdev_get_mpath(rdev, dev, dst, next_hop, &pinfo);
	if (err)
		return err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	if (nl80211_send_mpath(msg, info->snd_portid, info->snd_seq, 0,
				 dev, dst, next_hop, &pinfo) < 0) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	return genlmsg_reply(msg, info);
}