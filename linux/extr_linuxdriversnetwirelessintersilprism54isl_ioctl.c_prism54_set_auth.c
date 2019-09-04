#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union oid_res_t {int u; } ;
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_6__ {int wpa; int /*<<< orphan*/  mib_sem; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int DOT11_AUTH_OS ; 
 int DOT11_AUTH_SK ; 
 int DOT11_MLME_AUTO ; 
 int DOT11_MLME_EXTENDED ; 
 int /*<<< orphan*/  DOT11_OID_AUTHENABLE ; 
 int /*<<< orphan*/  DOT11_OID_DOT1XENABLE ; 
 int /*<<< orphan*/  DOT11_OID_EXUNENCRYPTED ; 
 int /*<<< orphan*/  DOT11_OID_MLMEAUTOLEVEL ; 
 int /*<<< orphan*/  DOT11_OID_PRIVACYINVOKED ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 136 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_CIPHER_GROUP 135 
#define  IW_AUTH_CIPHER_PAIRWISE 134 
#define  IW_AUTH_DROP_UNENCRYPTED 133 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 132 
#define  IW_AUTH_PRIVACY_INVOKED 131 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int IW_AUTH_WPA_VERSION_DISABLED ; 
 int IW_AUTH_WPA_VERSION_WPA ; 
 int IW_AUTH_WPA_VERSION_WPA2 ; 
 scalar_t__ PRV_STATE_INIT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ islpci_get_state (TYPE_1__*) ; 
 int mgt_get_request (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/  mgt_set_request (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism54_set_auth(struct net_device *ndev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct iw_param *param = &wrqu->param;
	u32 mlmelevel = 0, authen = 0, dot1x = 0;
	u32 exunencrypt = 0, privinvoked = 0, wpa = 0;
	u32 old_wpa;
	int ret = 0;
	union oid_res_t r;

	if (islpci_get_state(priv) < PRV_STATE_INIT)
		return 0;

	/* first get the flags */
	down_write(&priv->mib_sem);
	wpa = old_wpa = priv->wpa;
	up_write(&priv->mib_sem);
	ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, NULL, &r);
	authen = r.u;
	ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, NULL, &r);
	privinvoked = r.u;
	ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, NULL, &r);
	exunencrypt = r.u;
	ret = mgt_get_request(priv, DOT11_OID_DOT1XENABLE, 0, NULL, &r);
	dot1x = r.u;
	ret = mgt_get_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, NULL, &r);
	mlmelevel = r.u;

	if (ret < 0)
		goto out;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		break;

	case IW_AUTH_WPA_ENABLED:
		/* Do the same thing as IW_AUTH_WPA_VERSION */
		if (param->value) {
			wpa = 1;
			privinvoked = 1; /* For privacy invoked */
			exunencrypt = 1; /* Filter out all unencrypted frames */
			dot1x = 0x01; /* To enable eap filter */
			mlmelevel = DOT11_MLME_EXTENDED;
			authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */
		} else {
			wpa = 0;
			privinvoked = 0;
			exunencrypt = 0; /* Do not filter un-encrypted data */
			dot1x = 0;
			mlmelevel = DOT11_MLME_AUTO;
		}
		break;

	case IW_AUTH_WPA_VERSION:
		if (param->value & IW_AUTH_WPA_VERSION_DISABLED) {
			wpa = 0;
			privinvoked = 0;
			exunencrypt = 0; /* Do not filter un-encrypted data */
			dot1x = 0;
			mlmelevel = DOT11_MLME_AUTO;
		} else {
			if (param->value & IW_AUTH_WPA_VERSION_WPA)
				wpa = 1;
			else if (param->value & IW_AUTH_WPA_VERSION_WPA2)
				wpa = 2;
			privinvoked = 1; /* For privacy invoked */
			exunencrypt = 1; /* Filter out all unencrypted frames */
			dot1x = 0x01; /* To enable eap filter */
			mlmelevel = DOT11_MLME_EXTENDED;
			authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */
		}
		break;

	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		/* dot1x should be the opposite of RX_UNENCRYPTED_EAPOL;
		 * turn off dot1x when allowing receipt of unencrypted EAPOL
		 * frames, turn on dot1x when receipt should be disallowed
		 */
		dot1x = param->value ? 0 : 0x01;
		break;

	case IW_AUTH_PRIVACY_INVOKED:
		privinvoked = param->value ? 1 : 0;
		break;

	case IW_AUTH_DROP_UNENCRYPTED:
		exunencrypt = param->value ? 1 : 0;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		if (param->value & IW_AUTH_ALG_SHARED_KEY) {
			/* Only WEP uses _SK and _BOTH */
			if (wpa > 0) {
				ret = -EINVAL;
				goto out;
			}
			authen = DOT11_AUTH_SK;
		} else if (param->value & IW_AUTH_ALG_OPEN_SYSTEM) {
			authen = DOT11_AUTH_OS;
		} else {
			ret = -EINVAL;
			goto out;
		}
		break;

	default:
		return -EOPNOTSUPP;
	}

	/* Set all the values */
	down_write(&priv->mib_sem);
	priv->wpa = wpa;
	up_write(&priv->mib_sem);
	mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0, &authen);
	mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0, &privinvoked);
	mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0, &exunencrypt);
	mgt_set_request(priv, DOT11_OID_DOT1XENABLE, 0, &dot1x);
	mgt_set_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, &mlmelevel);

out:
	return ret;
}