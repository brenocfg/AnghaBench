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
struct wireless_dev {int iftype; int use_4addr; int /*<<< orphan*/  mesh_id_up_len; int /*<<< orphan*/  ssid; } ;
struct vif_params {int use_4addr; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wireless_dev* ieee80211_ptr; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IEEE80211_MAX_MESH_ID_LEN ; 
 scalar_t__ IEEE80211_MAX_SSID_LEN ; 
 size_t NL80211_ATTR_4ADDR ; 
 size_t NL80211_ATTR_IFTYPE ; 
 size_t NL80211_ATTR_MESH_ID ; 
 int /*<<< orphan*/  NL80211_CMD_SET_INTERFACE ; 
 int NL80211_IFTYPE_MESH_POINT ; 
 int cfg80211_change_iface (struct net_device*,struct net_device*,int,struct vif_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vif_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  nl80211_notify_iface (struct net_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int nl80211_parse_mon_options (struct net_device*,int,struct genl_info*,struct vif_params*) ; 
 int nl80211_valid_4addr (struct net_device*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_set_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct vif_params params;
	int err;
	enum nl80211_iftype otype, ntype;
	struct net_device *dev = info->user_ptr[1];
	bool change = false;

	memset(&params, 0, sizeof(params));

	otype = ntype = dev->ieee80211_ptr->iftype;

	if (info->attrs[NL80211_ATTR_IFTYPE]) {
		ntype = nla_get_u32(info->attrs[NL80211_ATTR_IFTYPE]);
		if (otype != ntype)
			change = true;
	}

	if (info->attrs[NL80211_ATTR_MESH_ID]) {
		struct wireless_dev *wdev = dev->ieee80211_ptr;

		if (ntype != NL80211_IFTYPE_MESH_POINT)
			return -EINVAL;
		if (netif_running(dev))
			return -EBUSY;

		wdev_lock(wdev);
		BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN !=
			     IEEE80211_MAX_MESH_ID_LEN);
		wdev->mesh_id_up_len =
			nla_len(info->attrs[NL80211_ATTR_MESH_ID]);
		memcpy(wdev->ssid, nla_data(info->attrs[NL80211_ATTR_MESH_ID]),
		       wdev->mesh_id_up_len);
		wdev_unlock(wdev);
	}

	if (info->attrs[NL80211_ATTR_4ADDR]) {
		params.use_4addr = !!nla_get_u8(info->attrs[NL80211_ATTR_4ADDR]);
		change = true;
		err = nl80211_valid_4addr(rdev, dev, params.use_4addr, ntype);
		if (err)
			return err;
	} else {
		params.use_4addr = -1;
	}

	err = nl80211_parse_mon_options(rdev, ntype, info, &params);
	if (err < 0)
		return err;
	if (err > 0)
		change = true;

	if (change)
		err = cfg80211_change_iface(rdev, dev, ntype, &params);
	else
		err = 0;

	if (!err && params.use_4addr != -1)
		dev->ieee80211_ptr->use_4addr = params.use_4addr;

	if (change && !err) {
		struct wireless_dev *wdev = dev->ieee80211_ptr;

		nl80211_notify_iface(rdev, wdev, NL80211_CMD_SET_INTERFACE);
	}

	return err;
}