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
struct wiphy {int regulatory_flags; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_regdomain {int dummy; } ;
struct genl_info {scalar_t__* attrs; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;
struct cfg80211_registered_device {struct wiphy wiphy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct cfg80211_registered_device*) ; 
 size_t NL80211_ATTR_USER_REG_HINT_TYPE ; 
 size_t NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_GET_REG ; 
 int /*<<< orphan*/  NL80211_USER_REG_HINT_CELL_BASE ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (struct cfg80211_registered_device*) ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 scalar_t__ WARN_ON (int) ; 
 struct cfg80211_registered_device* cfg80211_get_dev_from_info (int /*<<< orphan*/ ,struct genl_info*) ; 
 int /*<<< orphan*/  cfg80211_regdomain ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  get_wiphy_idx (struct wiphy*) ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 scalar_t__ nl80211_put_regdom (struct ieee80211_regdomain const*,struct sk_buff*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_regdomain* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ reg_last_request_cell_base () ; 

__attribute__((used)) static int nl80211_get_reg_do(struct sk_buff *skb, struct genl_info *info)
{
	const struct ieee80211_regdomain *regdom = NULL;
	struct cfg80211_registered_device *rdev;
	struct wiphy *wiphy = NULL;
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOBUFS;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_REG);
	if (!hdr)
		goto put_failure;

	if (info->attrs[NL80211_ATTR_WIPHY]) {
		bool self_managed;

		rdev = cfg80211_get_dev_from_info(genl_info_net(info), info);
		if (IS_ERR(rdev)) {
			nlmsg_free(msg);
			return PTR_ERR(rdev);
		}

		wiphy = &rdev->wiphy;
		self_managed = wiphy->regulatory_flags &
			       REGULATORY_WIPHY_SELF_MANAGED;
		regdom = get_wiphy_regdom(wiphy);

		/* a self-managed-reg device must have a private regdom */
		if (WARN_ON(!regdom && self_managed)) {
			nlmsg_free(msg);
			return -EINVAL;
		}

		if (regdom &&
		    nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
			goto nla_put_failure;
	}

	if (!wiphy && reg_last_request_cell_base() &&
	    nla_put_u32(msg, NL80211_ATTR_USER_REG_HINT_TYPE,
			NL80211_USER_REG_HINT_CELL_BASE))
		goto nla_put_failure;

	rcu_read_lock();

	if (!regdom)
		regdom = rcu_dereference(cfg80211_regdomain);

	if (nl80211_put_regdom(regdom, msg))
		goto nla_put_failure_rcu;

	rcu_read_unlock();

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

nla_put_failure_rcu:
	rcu_read_unlock();
nla_put_failure:
put_failure:
	nlmsg_free(msg);
	return -EMSGSIZE;
}