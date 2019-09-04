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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {int /*<<< orphan*/ * attrs; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  probe_client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_ATTR_COOKIE ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_CMD_PROBE_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_probe_client (struct net_device*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_probe_client(struct sk_buff *skb,
				struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct sk_buff *msg;
	void *hdr;
	const u8 *addr;
	u64 cookie;
	int err;

	if (wdev->iftype != NL80211_IFTYPE_AP &&
	    wdev->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	if (!rdev->ops->probe_client)
		return -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_PROBE_CLIENT);
	if (!hdr) {
		err = -ENOBUFS;
		goto free_msg;
	}

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	err = rdev_probe_client(rdev, dev, addr, &cookie);
	if (err)
		goto free_msg;

	if (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	return genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 free_msg:
	nlmsg_free(msg);
	return err;
}