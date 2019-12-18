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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int flags; } ;
struct net_device {TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tdls_mgmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_STATUS_CODE ; 
 size_t NL80211_ATTR_TDLS_ACTION ; 
 size_t NL80211_ATTR_TDLS_DIALOG_TOKEN ; 
 size_t NL80211_ATTR_TDLS_INITIATOR ; 
 size_t NL80211_ATTR_TDLS_PEER_CAPABILITY ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int /*<<< orphan*/ * nla_data (scalar_t__) ; 
 int nla_get_flag (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int rdev_tdls_mgmt (struct net_device*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_tdls_mgmt(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	u8 action_code, dialog_token;
	u32 peer_capability = 0;
	u16 status_code;
	u8 *peer;
	bool initiator;

	if (!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) ||
	    !rdev->ops->tdls_mgmt)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_TDLS_ACTION] ||
	    !info->attrs[NL80211_ATTR_STATUS_CODE] ||
	    !info->attrs[NL80211_ATTR_TDLS_DIALOG_TOKEN] ||
	    !info->attrs[NL80211_ATTR_IE] ||
	    !info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);
	action_code = nla_get_u8(info->attrs[NL80211_ATTR_TDLS_ACTION]);
	status_code = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);
	dialog_token = nla_get_u8(info->attrs[NL80211_ATTR_TDLS_DIALOG_TOKEN]);
	initiator = nla_get_flag(info->attrs[NL80211_ATTR_TDLS_INITIATOR]);
	if (info->attrs[NL80211_ATTR_TDLS_PEER_CAPABILITY])
		peer_capability =
			nla_get_u32(info->attrs[NL80211_ATTR_TDLS_PEER_CAPABILITY]);

	return rdev_tdls_mgmt(rdev, dev, peer, action_code,
			      dialog_token, status_code, peer_capability,
			      initiator,
			      nla_data(info->attrs[NL80211_ATTR_IE]),
			      nla_len(info->attrs[NL80211_ATTR_IE]));
}