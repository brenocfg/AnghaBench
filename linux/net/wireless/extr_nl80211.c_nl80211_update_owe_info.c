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
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_update_owe_info {int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  peer; int /*<<< orphan*/  status; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  owe_info ;
struct TYPE_2__ {int /*<<< orphan*/  update_owe_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_STATUS_CODE ; 
 int /*<<< orphan*/  memset (struct cfg80211_update_owe_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int rdev_update_owe_info (struct net_device*,struct net_device*,struct cfg80211_update_owe_info*) ; 

__attribute__((used)) static int nl80211_update_owe_info(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct cfg80211_update_owe_info owe_info;
	struct net_device *dev = info->user_ptr[1];

	if (!rdev->ops->update_owe_info)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_STATUS_CODE] ||
	    !info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	memset(&owe_info, 0, sizeof(owe_info));
	owe_info.status = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);
	nla_memcpy(owe_info.peer, info->attrs[NL80211_ATTR_MAC], ETH_ALEN);

	if (info->attrs[NL80211_ATTR_IE]) {
		owe_info.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		owe_info.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	return rdev_update_owe_info(rdev, dev, &owe_info);
}