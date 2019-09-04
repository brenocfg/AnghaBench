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
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int privacy_invoked; int /*<<< orphan*/  authenticate_type; } ;
struct TYPE_3__ {int version; int rsn_enabled; int pairwise_suite; int group_suite; int key_mgmt_suite; int auth_alg; int wpa_enabled; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; scalar_t__ need_commit; TYPE_2__ reg; TYPE_1__ wpa; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_TYPE_OPEN_SYSTEM ; 
 int /*<<< orphan*/  AUTH_TYPE_SHARED_KEY ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  IW_AUTH_80211_AUTH_ALG 151 
#define  IW_AUTH_ALG_LEAP 150 
#define  IW_AUTH_ALG_OPEN_SYSTEM 149 
#define  IW_AUTH_ALG_SHARED_KEY 148 
#define  IW_AUTH_CIPHER_CCMP 147 
#define  IW_AUTH_CIPHER_GROUP 146 
#define  IW_AUTH_CIPHER_NONE 145 
#define  IW_AUTH_CIPHER_PAIRWISE 144 
#define  IW_AUTH_CIPHER_TKIP 143 
#define  IW_AUTH_CIPHER_WEP104 142 
#define  IW_AUTH_CIPHER_WEP40 141 
#define  IW_AUTH_DROP_UNENCRYPTED 140 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 139 
#define  IW_AUTH_KEY_MGMT_802_1X 138 
#define  IW_AUTH_KEY_MGMT_PSK 137 
#define  IW_AUTH_PRIVACY_INVOKED 136 
#define  IW_AUTH_ROAMING_CONTROL 135 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 134 
#define  IW_AUTH_TKIP_COUNTERMEASURES 133 
#define  IW_AUTH_WPA_ENABLED 132 
#define  IW_AUTH_WPA_VERSION 131 
#define  IW_AUTH_WPA_VERSION_DISABLED 130 
#define  IW_AUTH_WPA_VERSION_WPA 129 
#define  IW_AUTH_WPA_VERSION_WPA2 128 
 scalar_t__ SLP_SLEEP ; 
 scalar_t__ SME_MODE_SET ; 
 scalar_t__ SME_RSN ; 
 scalar_t__ SME_RSN_AUTH ; 
 scalar_t__ SME_RSN_MULTICAST ; 
 scalar_t__ SME_RSN_UNICAST ; 
 scalar_t__ SME_WEP_FLAG ; 
 int /*<<< orphan*/  ks_wlan_setup_parameter (struct ks_wlan_private*,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_auth_mode(struct net_device *dev,
				 struct iw_request_info *info,
				 union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_param *param = &vwrq->param;
	int index = (param->flags & IW_AUTH_INDEX);
	int value = param->value;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;
	/* for SLEEP MODE */
	switch (index) {
	case IW_AUTH_WPA_VERSION:	/* 0 */
		switch (value) {
		case IW_AUTH_WPA_VERSION_DISABLED:
			priv->wpa.version = value;
			if (priv->wpa.rsn_enabled)
				priv->wpa.rsn_enabled = false;
			priv->need_commit |= SME_RSN;
			break;
		case IW_AUTH_WPA_VERSION_WPA:
		case IW_AUTH_WPA_VERSION_WPA2:
			priv->wpa.version = value;
			if (!(priv->wpa.rsn_enabled))
				priv->wpa.rsn_enabled = true;
			priv->need_commit |= SME_RSN;
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	case IW_AUTH_CIPHER_PAIRWISE:	/* 1 */
		switch (value) {
		case IW_AUTH_CIPHER_NONE:
			if (priv->reg.privacy_invoked) {
				priv->reg.privacy_invoked = 0x00;
				priv->need_commit |= SME_WEP_FLAG;
			}
			break;
		case IW_AUTH_CIPHER_WEP40:
		case IW_AUTH_CIPHER_TKIP:
		case IW_AUTH_CIPHER_CCMP:
		case IW_AUTH_CIPHER_WEP104:
			if (!priv->reg.privacy_invoked) {
				priv->reg.privacy_invoked = 0x01;
				priv->need_commit |= SME_WEP_FLAG;
			}
			priv->wpa.pairwise_suite = value;
			priv->need_commit |= SME_RSN_UNICAST;
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	case IW_AUTH_CIPHER_GROUP:	/* 2 */
		switch (value) {
		case IW_AUTH_CIPHER_NONE:
			if (priv->reg.privacy_invoked) {
				priv->reg.privacy_invoked = 0x00;
				priv->need_commit |= SME_WEP_FLAG;
			}
			break;
		case IW_AUTH_CIPHER_WEP40:
		case IW_AUTH_CIPHER_TKIP:
		case IW_AUTH_CIPHER_CCMP:
		case IW_AUTH_CIPHER_WEP104:
			if (!priv->reg.privacy_invoked) {
				priv->reg.privacy_invoked = 0x01;
				priv->need_commit |= SME_WEP_FLAG;
			}
			priv->wpa.group_suite = value;
			priv->need_commit |= SME_RSN_MULTICAST;
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	case IW_AUTH_KEY_MGMT:	/* 3 */
		switch (value) {
		case IW_AUTH_KEY_MGMT_802_1X:
		case IW_AUTH_KEY_MGMT_PSK:
		case 0:	/* NONE or 802_1X_NO_WPA */
		case 4:	/* WPA_NONE */
			priv->wpa.key_mgmt_suite = value;
			priv->need_commit |= SME_RSN_AUTH;
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	case IW_AUTH_80211_AUTH_ALG:	/* 6 */
		switch (value) {
		case IW_AUTH_ALG_OPEN_SYSTEM:
			priv->wpa.auth_alg = value;
			priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
			break;
		case IW_AUTH_ALG_SHARED_KEY:
			priv->wpa.auth_alg = value;
			priv->reg.authenticate_type = AUTH_TYPE_SHARED_KEY;
			break;
		case IW_AUTH_ALG_LEAP:
		default:
			return -EOPNOTSUPP;
		}
		priv->need_commit |= SME_MODE_SET;
		break;
	case IW_AUTH_WPA_ENABLED:	/* 7 */
		priv->wpa.wpa_enabled = value;
		break;
	case IW_AUTH_PRIVACY_INVOKED:	/* 10 */
		if ((value && !priv->reg.privacy_invoked) ||
		    (!value && priv->reg.privacy_invoked)) {
			priv->reg.privacy_invoked = value ? 0x01 : 0x00;
			priv->need_commit |= SME_WEP_FLAG;
		}
		break;
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:	/* 4 */
	case IW_AUTH_TKIP_COUNTERMEASURES:	/* 5 */
	case IW_AUTH_DROP_UNENCRYPTED:	/* 8 */
	case IW_AUTH_ROAMING_CONTROL:	/* 9 */
	default:
		break;
	}

	/* return -EINPROGRESS; */
	if (priv->need_commit) {
		ks_wlan_setup_parameter(priv, priv->need_commit);
		priv->need_commit = 0;
	}
	return 0;
}