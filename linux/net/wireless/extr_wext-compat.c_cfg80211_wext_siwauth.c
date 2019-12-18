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
struct TYPE_3__ {int /*<<< orphan*/  privacy; } ;
struct TYPE_4__ {TYPE_1__ connect; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_2__ wext; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
#define  IW_AUTH_CIPHER_GROUP 136 
#define  IW_AUTH_CIPHER_PAIRWISE 135 
#define  IW_AUTH_DROP_UNENCRYPTED 134 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 133 
#define  IW_AUTH_MFP 132 
#define  IW_AUTH_PRIVACY_INVOKED 131 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int cfg80211_set_auth_alg (struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int cfg80211_set_cipher_group (struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int cfg80211_set_cipher_pairwise (struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int cfg80211_set_key_mgt (struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int cfg80211_set_wpa_version (struct wireless_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_siwauth(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *data, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	switch (data->flags & IW_AUTH_INDEX) {
	case IW_AUTH_PRIVACY_INVOKED:
		wdev->wext.connect.privacy = data->value;
		return 0;
	case IW_AUTH_WPA_VERSION:
		return cfg80211_set_wpa_version(wdev, data->value);
	case IW_AUTH_CIPHER_GROUP:
		return cfg80211_set_cipher_group(wdev, data->value);
	case IW_AUTH_KEY_MGMT:
		return cfg80211_set_key_mgt(wdev, data->value);
	case IW_AUTH_CIPHER_PAIRWISE:
		return cfg80211_set_cipher_pairwise(wdev, data->value);
	case IW_AUTH_80211_AUTH_ALG:
		return cfg80211_set_auth_alg(wdev, data->value);
	case IW_AUTH_WPA_ENABLED:
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
	case IW_AUTH_DROP_UNENCRYPTED:
	case IW_AUTH_MFP:
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}