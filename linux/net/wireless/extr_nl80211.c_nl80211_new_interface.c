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
struct wireless_dev {int /*<<< orphan*/  mesh_id_up_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  owner_nlportid; } ;
struct vif_params {int use_4addr; int /*<<< orphan*/  macaddr; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; scalar_t__* attrs; struct cfg80211_registered_device** user_ptr; } ;
struct TYPE_4__ {int features; } ;
struct cfg80211_registered_device {TYPE_2__ wiphy; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_3__ {int /*<<< orphan*/  add_virtual_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPROTO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_MAX_MESH_ID_LEN ; 
 int /*<<< orphan*/  IEEE80211_MAX_SSID_LEN ; 
 scalar_t__ IS_ERR (struct wireless_dev*) ; 
 int /*<<< orphan*/  NET_NAME_USER ; 
 size_t NL80211_ATTR_4ADDR ; 
 size_t NL80211_ATTR_IFNAME ; 
 size_t NL80211_ATTR_IFTYPE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MESH_ID ; 
 size_t NL80211_ATTR_SOCKET_OWNER ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_INTERFACE ; 
 int NL80211_FEATURE_MAC_ON_CREATE ; 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_NAN 129 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (struct wireless_dev*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_destroy_ifaces (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_iftype_allowed (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_init_wdev (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vif_params*,int /*<<< orphan*/ ,int) ; 
 int nl80211_parse_mon_options (struct cfg80211_registered_device*,int,struct genl_info*,struct vif_params*) ; 
 scalar_t__ nl80211_send_iface (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int nl80211_valid_4addr (struct cfg80211_registered_device*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wireless_dev* rdev_add_virtual_intf (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vif_params*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_new_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct vif_params params;
	struct wireless_dev *wdev;
	struct sk_buff *msg;
	int err;
	enum nl80211_iftype type = NL80211_IFTYPE_UNSPECIFIED;

	/* to avoid failing a new interface creation due to pending removal */
	cfg80211_destroy_ifaces(rdev);

	memset(&params, 0, sizeof(params));

	if (!info->attrs[NL80211_ATTR_IFNAME])
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_IFTYPE])
		type = nla_get_u32(info->attrs[NL80211_ATTR_IFTYPE]);

	if (!rdev->ops->add_virtual_intf)
		return -EOPNOTSUPP;

	if ((type == NL80211_IFTYPE_P2P_DEVICE || type == NL80211_IFTYPE_NAN ||
	     rdev->wiphy.features & NL80211_FEATURE_MAC_ON_CREATE) &&
	    info->attrs[NL80211_ATTR_MAC]) {
		nla_memcpy(params.macaddr, info->attrs[NL80211_ATTR_MAC],
			   ETH_ALEN);
		if (!is_valid_ether_addr(params.macaddr))
			return -EADDRNOTAVAIL;
	}

	if (info->attrs[NL80211_ATTR_4ADDR]) {
		params.use_4addr = !!nla_get_u8(info->attrs[NL80211_ATTR_4ADDR]);
		err = nl80211_valid_4addr(rdev, NULL, params.use_4addr, type);
		if (err)
			return err;
	}

	if (!cfg80211_iftype_allowed(&rdev->wiphy, type, params.use_4addr, 0))
		return -EOPNOTSUPP;

	err = nl80211_parse_mon_options(rdev, type, info, &params);
	if (err < 0)
		return err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	wdev = rdev_add_virtual_intf(rdev,
				nla_data(info->attrs[NL80211_ATTR_IFNAME]),
				NET_NAME_USER, type, &params);
	if (WARN_ON(!wdev)) {
		nlmsg_free(msg);
		return -EPROTO;
	} else if (IS_ERR(wdev)) {
		nlmsg_free(msg);
		return PTR_ERR(wdev);
	}

	if (info->attrs[NL80211_ATTR_SOCKET_OWNER])
		wdev->owner_nlportid = info->snd_portid;

	switch (type) {
	case NL80211_IFTYPE_MESH_POINT:
		if (!info->attrs[NL80211_ATTR_MESH_ID])
			break;
		wdev_lock(wdev);
		BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN !=
			     IEEE80211_MAX_MESH_ID_LEN);
		wdev->mesh_id_up_len =
			nla_len(info->attrs[NL80211_ATTR_MESH_ID]);
		memcpy(wdev->ssid, nla_data(info->attrs[NL80211_ATTR_MESH_ID]),
		       wdev->mesh_id_up_len);
		wdev_unlock(wdev);
		break;
	case NL80211_IFTYPE_NAN:
	case NL80211_IFTYPE_P2P_DEVICE:
		/*
		 * P2P Device and NAN do not have a netdev, so don't go
		 * through the netdev notifier and must be added here
		 */
		cfg80211_init_wdev(rdev, wdev);
		break;
	default:
		break;
	}

	if (nl80211_send_iface(msg, info->snd_portid, info->snd_seq, 0,
			       rdev, wdev, NL80211_CMD_NEW_INTERFACE) < 0) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	return genlmsg_reply(msg, info);
}