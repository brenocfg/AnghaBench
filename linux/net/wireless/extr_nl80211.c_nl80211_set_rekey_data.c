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
struct wireless_dev {int /*<<< orphan*/  current_bss; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_gtk_rekey_data {void* replay_ctr; void* kck; void* kek; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_rekey_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int /*<<< orphan*/  MAX_NL80211_REKEY_DATA ; 
 size_t NL80211_ATTR_REKEY_DATA ; 
 scalar_t__ NL80211_KCK_LEN ; 
 scalar_t__ NL80211_KEK_LEN ; 
 size_t NL80211_REKEY_DATA_KCK ; 
 size_t NL80211_REKEY_DATA_KEK ; 
 size_t NL80211_REKEY_DATA_REPLAY_CTR ; 
 scalar_t__ NL80211_REPLAY_CTR_LEN ; 
 int NUM_NL80211_REKEY_DATA ; 
 int /*<<< orphan*/  nl80211_rekey_policy ; 
 void* nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_set_rekey_data (struct net_device*,struct net_device*,struct cfg80211_gtk_rekey_data*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_set_rekey_data(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct nlattr *tb[NUM_NL80211_REKEY_DATA];
	struct cfg80211_gtk_rekey_data rekey_data;
	int err;

	if (!info->attrs[NL80211_ATTR_REKEY_DATA])
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, MAX_NL80211_REKEY_DATA,
					  info->attrs[NL80211_ATTR_REKEY_DATA],
					  nl80211_rekey_policy, info->extack);
	if (err)
		return err;

	if (!tb[NL80211_REKEY_DATA_REPLAY_CTR] || !tb[NL80211_REKEY_DATA_KEK] ||
	    !tb[NL80211_REKEY_DATA_KCK])
		return -EINVAL;
	if (nla_len(tb[NL80211_REKEY_DATA_REPLAY_CTR]) != NL80211_REPLAY_CTR_LEN)
		return -ERANGE;
	if (nla_len(tb[NL80211_REKEY_DATA_KEK]) != NL80211_KEK_LEN)
		return -ERANGE;
	if (nla_len(tb[NL80211_REKEY_DATA_KCK]) != NL80211_KCK_LEN)
		return -ERANGE;

	rekey_data.kek = nla_data(tb[NL80211_REKEY_DATA_KEK]);
	rekey_data.kck = nla_data(tb[NL80211_REKEY_DATA_KCK]);
	rekey_data.replay_ctr = nla_data(tb[NL80211_REKEY_DATA_REPLAY_CTR]);

	wdev_lock(wdev);
	if (!wdev->current_bss) {
		err = -ENOTCONN;
		goto out;
	}

	if (!rdev->ops->set_rekey_data) {
		err = -EOPNOTSUPP;
		goto out;
	}

	err = rdev_set_rekey_data(rdev, dev, &rekey_data);
 out:
	wdev_unlock(wdev);
	return err;
}