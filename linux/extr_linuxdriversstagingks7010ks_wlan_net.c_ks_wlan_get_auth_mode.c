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
struct iw_param {int flags; int /*<<< orphan*/  value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsn_enabled; int /*<<< orphan*/  auth_alg; int /*<<< orphan*/  key_mgmt_suite; int /*<<< orphan*/  group_suite; int /*<<< orphan*/  pairwise_suite; int /*<<< orphan*/  version; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ wpa; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
#define  IW_AUTH_80211_AUTH_ALG 136 
#define  IW_AUTH_CIPHER_GROUP 135 
#define  IW_AUTH_CIPHER_PAIRWISE 134 
#define  IW_AUTH_DROP_UNENCRYPTED 133 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 scalar_t__ SLP_SLEEP ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_auth_mode(struct net_device *dev,
				 struct iw_request_info *info,
				 union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_param *param = &vwrq->param;
	int index = (param->flags & IW_AUTH_INDEX);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	/*  WPA (not used ?? wpa_supplicant) */
	switch (index) {
	case IW_AUTH_WPA_VERSION:
		param->value = priv->wpa.version;
		break;
	case IW_AUTH_CIPHER_PAIRWISE:
		param->value = priv->wpa.pairwise_suite;
		break;
	case IW_AUTH_CIPHER_GROUP:
		param->value = priv->wpa.group_suite;
		break;
	case IW_AUTH_KEY_MGMT:
		param->value = priv->wpa.key_mgmt_suite;
		break;
	case IW_AUTH_80211_AUTH_ALG:
		param->value = priv->wpa.auth_alg;
		break;
	case IW_AUTH_WPA_ENABLED:
		param->value = priv->wpa.rsn_enabled;
		break;
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:	/* OK??? */
	case IW_AUTH_TKIP_COUNTERMEASURES:
	case IW_AUTH_DROP_UNENCRYPTED:
	default:
		/* return -EOPNOTSUPP; */
		break;
	}
	return 0;
}