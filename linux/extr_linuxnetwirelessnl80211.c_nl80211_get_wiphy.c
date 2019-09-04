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
struct sk_buff {int dummy; } ;
struct nl80211_dump_wiphy_state {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct cfg80211_registered_device** user_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_WIPHY ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 scalar_t__ nl80211_send_wiphy (struct cfg80211_registered_device*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nl80211_dump_wiphy_state*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_get_wiphy(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct nl80211_dump_wiphy_state state = {};

	msg = nlmsg_new(4096, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	if (nl80211_send_wiphy(rdev, NL80211_CMD_NEW_WIPHY, msg,
			       info->snd_portid, info->snd_seq, 0,
			       &state) < 0) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	return genlmsg_reply(msg, info);
}