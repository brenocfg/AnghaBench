#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int default_mgmt_key; int default_key; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_2__ wext; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct key_params {int key_len; int seq_len; int /*<<< orphan*/  seq; scalar_t__ cipher; int /*<<< orphan*/  key; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sa_data; } ;
struct iw_encode_ext {int alg; int key_len; int ext_flags; int /*<<< orphan*/  rx_seq; int /*<<< orphan*/  key; TYPE_3__ addr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int /*<<< orphan*/  set_default_key; int /*<<< orphan*/  add_key; int /*<<< orphan*/  del_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_ENCODE_ALG_AES_CMAC 132 
#define  IW_ENCODE_ALG_CCMP 131 
#define  IW_ENCODE_ALG_NONE 130 
#define  IW_ENCODE_ALG_TKIP 129 
#define  IW_ENCODE_ALG_WEP 128 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_RX_SEQ_VALID ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int IW_ENCODE_INDEX ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WLAN_CIPHER_SUITE_AES_CMAC ; 
 scalar_t__ WLAN_CIPHER_SUITE_CCMP ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int cfg80211_set_encryption (struct cfg80211_registered_device*,struct net_device*,int,int /*<<< orphan*/  const*,int,int,int,struct key_params*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (struct key_params*,int /*<<< orphan*/ ,int) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_siwencodeext(struct net_device *dev,
				      struct iw_request_info *info,
				      struct iw_point *erq, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct iw_encode_ext *ext = (struct iw_encode_ext *) extra;
	const u8 *addr;
	int idx;
	bool remove = false;
	struct key_params params;
	u32 cipher;

	if (wdev->iftype != NL80211_IFTYPE_STATION &&
	    wdev->iftype != NL80211_IFTYPE_ADHOC)
		return -EOPNOTSUPP;

	/* no use -- only MFP (set_default_mgmt_key) is optional */
	if (!rdev->ops->del_key ||
	    !rdev->ops->add_key ||
	    !rdev->ops->set_default_key)
		return -EOPNOTSUPP;

	switch (ext->alg) {
	case IW_ENCODE_ALG_NONE:
		remove = true;
		cipher = 0;
		break;
	case IW_ENCODE_ALG_WEP:
		if (ext->key_len == 5)
			cipher = WLAN_CIPHER_SUITE_WEP40;
		else if (ext->key_len == 13)
			cipher = WLAN_CIPHER_SUITE_WEP104;
		else
			return -EINVAL;
		break;
	case IW_ENCODE_ALG_TKIP:
		cipher = WLAN_CIPHER_SUITE_TKIP;
		break;
	case IW_ENCODE_ALG_CCMP:
		cipher = WLAN_CIPHER_SUITE_CCMP;
		break;
	case IW_ENCODE_ALG_AES_CMAC:
		cipher = WLAN_CIPHER_SUITE_AES_CMAC;
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (erq->flags & IW_ENCODE_DISABLED)
		remove = true;

	idx = erq->flags & IW_ENCODE_INDEX;
	if (cipher == WLAN_CIPHER_SUITE_AES_CMAC) {
		if (idx < 4 || idx > 5) {
			idx = wdev->wext.default_mgmt_key;
			if (idx < 0)
				return -EINVAL;
		} else
			idx--;
	} else {
		if (idx < 1 || idx > 4) {
			idx = wdev->wext.default_key;
			if (idx < 0)
				return -EINVAL;
		} else
			idx--;
	}

	addr = ext->addr.sa_data;
	if (is_broadcast_ether_addr(addr))
		addr = NULL;

	memset(&params, 0, sizeof(params));
	params.key = ext->key;
	params.key_len = ext->key_len;
	params.cipher = cipher;

	if (ext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID) {
		params.seq = ext->rx_seq;
		params.seq_len = 6;
	}

	return cfg80211_set_encryption(
			rdev, dev,
			!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY),
			addr, remove,
			ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY,
			idx, &params);
}