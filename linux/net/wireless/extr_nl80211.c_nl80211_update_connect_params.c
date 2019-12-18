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
typedef  scalar_t__ u32 ;
struct wireless_dev {int /*<<< orphan*/  current_bss; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct cfg80211_connect_params {scalar_t__ auth_type; void* fils_erp_rrk_len; void* fils_erp_rrk; int /*<<< orphan*/  fils_erp_next_seq_num; void* fils_erp_realm_len; void* fils_erp_realm; void* fils_erp_username_len; void* fils_erp_username; void* ie_len; void* ie; } ;
struct TYPE_2__ {int /*<<< orphan*/  update_connect_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOLINK ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_AUTH_TYPE ; 
 size_t NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM ; 
 size_t NL80211_ATTR_FILS_ERP_REALM ; 
 size_t NL80211_ATTR_FILS_ERP_RRK ; 
 size_t NL80211_ATTR_FILS_ERP_USERNAME ; 
 size_t NL80211_ATTR_IE ; 
 scalar_t__ NL80211_AUTHTYPE_FILS_SK ; 
 int /*<<< orphan*/  NL80211_CMD_CONNECT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD ; 
 scalar_t__ UPDATE_ASSOC_IES ; 
 scalar_t__ UPDATE_AUTH_TYPE ; 
 scalar_t__ UPDATE_FILS_ERP_INFO ; 
 int /*<<< orphan*/  nl80211_valid_auth_type (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 scalar_t__ nla_get_u32 (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 
 int rdev_update_connect_params (struct net_device*,struct net_device*,struct cfg80211_connect_params*,scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 int wiphy_ext_feature_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_update_connect_params(struct sk_buff *skb,
					 struct genl_info *info)
{
	struct cfg80211_connect_params connect = {};
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	bool fils_sk_offload;
	u32 auth_type;
	u32 changed = 0;
	int ret;

	if (!rdev->ops->update_connect_params)
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_IE]) {
		connect.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		connect.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
		changed |= UPDATE_ASSOC_IES;
	}

	fils_sk_offload = wiphy_ext_feature_isset(&rdev->wiphy,
						  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD);

	/*
	 * when driver supports fils-sk offload all attributes must be
	 * provided. So the else covers "fils-sk-not-all" and
	 * "no-fils-sk-any".
	 */
	if (fils_sk_offload &&
	    info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_REALM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_RRK]) {
		connect.fils_erp_username =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_username_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_realm =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_realm_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_next_seq_num =
			nla_get_u16(
			   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM]);
		connect.fils_erp_rrk =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		connect.fils_erp_rrk_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		changed |= UPDATE_FILS_ERP_INFO;
	} else if (info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_REALM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_RRK]) {
		return -EINVAL;
	}

	if (info->attrs[NL80211_ATTR_AUTH_TYPE]) {
		auth_type = nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
		if (!nl80211_valid_auth_type(rdev, auth_type,
					     NL80211_CMD_CONNECT))
			return -EINVAL;

		if (auth_type == NL80211_AUTHTYPE_FILS_SK &&
		    fils_sk_offload && !(changed & UPDATE_FILS_ERP_INFO))
			return -EINVAL;

		connect.auth_type = auth_type;
		changed |= UPDATE_AUTH_TYPE;
	}

	wdev_lock(dev->ieee80211_ptr);
	if (!wdev->current_bss)
		ret = -ENOLINK;
	else
		ret = rdev_update_connect_params(rdev, dev, &connect, changed);
	wdev_unlock(dev->ieee80211_ptr);

	return ret;
}