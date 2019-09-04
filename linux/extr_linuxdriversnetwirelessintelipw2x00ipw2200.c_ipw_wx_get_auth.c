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
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int auth_mode; } ;
struct TYPE_4__ {size_t tx_keyidx; struct lib80211_crypt_data** crypt; } ;
struct libipw_device {int drop_unencrypted; int wpa_enabled; int ieee802_1x; int privacy_invoked; TYPE_3__ sec; TYPE_1__ crypt_info; } ;
struct lib80211_crypt_data {int /*<<< orphan*/  priv; TYPE_2__* ops; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {struct libipw_device* ieee; } ;
struct TYPE_5__ {int (* get_flags ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_CRYPTO_TKIP_COUNTERMEASURES ; 
#define  IW_AUTH_80211_AUTH_ALG 138 
#define  IW_AUTH_CIPHER_GROUP 137 
#define  IW_AUTH_CIPHER_PAIRWISE 136 
#define  IW_AUTH_DROP_UNENCRYPTED 135 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 134 
#define  IW_AUTH_PRIVACY_INVOKED 133 
#define  IW_AUTH_ROAMING_CONTROL 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_wx_get_auth(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct libipw_device *ieee = priv->ieee;
	struct lib80211_crypt_data *crypt;
	struct iw_param *param = &wrqu->param;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VERSION:
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		/*
		 * wpa_supplicant will control these internally
		 */
		return -EOPNOTSUPP;

	case IW_AUTH_TKIP_COUNTERMEASURES:
		crypt = priv->ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx];
		if (!crypt || !crypt->ops->get_flags)
			break;

		param->value = (crypt->ops->get_flags(crypt->priv) &
				IEEE80211_CRYPTO_TKIP_COUNTERMEASURES) ? 1 : 0;

		break;

	case IW_AUTH_DROP_UNENCRYPTED:
		param->value = ieee->drop_unencrypted;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		param->value = ieee->sec.auth_mode;
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = ieee->wpa_enabled;
		break;

	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		param->value = ieee->ieee802_1x;
		break;

	case IW_AUTH_ROAMING_CONTROL:
	case IW_AUTH_PRIVACY_INVOKED:
		param->value = ieee->privacy_invoked;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return 0;
}