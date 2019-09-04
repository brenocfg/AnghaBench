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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {int iftype; int /*<<< orphan*/  current_bss; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; int /*<<< orphan*/  wiphy; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; int /*<<< orphan*/  wiphy; struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_control_port; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GENL_SET_ERR_MSG (struct genl_info*,char*) ; 
 size_t NL80211_ATTR_CONTROL_PORT_ETHERTYPE ; 
 size_t NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT ; 
 size_t NL80211_ATTR_FRAME ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211 ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* nla_data (int /*<<< orphan*/ ) ; 
 int nla_get_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (int /*<<< orphan*/ ) ; 
 size_t nla_len (int /*<<< orphan*/ ) ; 
 int rdev_tx_control_port (struct net_device*,struct net_device*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_tx_control_port(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const u8 *buf;
	size_t len;
	u8 *dest;
	u16 proto;
	bool noencrypt;
	int err;

	if (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211))
		return -EOPNOTSUPP;

	if (!rdev->ops->tx_control_port)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_FRAME] ||
	    !info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]) {
		GENL_SET_ERR_MSG(info, "Frame, MAC or ethertype missing");
		return -EINVAL;
	}

	wdev_lock(wdev);

	switch (wdev->iftype) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_MESH_POINT:
		break;
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		if (wdev->current_bss)
			break;
		err = -ENOTCONN;
		goto out;
	default:
		err = -EOPNOTSUPP;
		goto out;
	}

	wdev_unlock(wdev);

	buf = nla_data(info->attrs[NL80211_ATTR_FRAME]);
	len = nla_len(info->attrs[NL80211_ATTR_FRAME]);
	dest = nla_data(info->attrs[NL80211_ATTR_MAC]);
	proto = nla_get_u16(info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]);
	noencrypt =
		nla_get_flag(info->attrs[NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT]);

	return rdev_tx_control_port(rdev, dev, buf, len,
				    dest, cpu_to_be16(proto), noencrypt);

 out:
	wdev_unlock(wdev);
	return err;
}