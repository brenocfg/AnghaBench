#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_6__ {int tkip_countermeasures; int drop_unencrypted; int auth_algs; int wpa; int host_roaming; int privacy_invoked; int ieee_802_1x; TYPE_1__* func; int /*<<< orphan*/  sta_fw_ver; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_port ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HFA384X_RID_SSNHANDLINGMODE ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
#define  IW_AUTH_CIPHER_GROUP 136 
#define  IW_AUTH_CIPHER_PAIRWISE 135 
#define  IW_AUTH_DROP_UNENCRYPTED 134 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 133 
#define  IW_AUTH_PRIVACY_INVOKED 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int /*<<< orphan*/  PRISM2_FW_VER (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_set_encryption (TYPE_2__*) ; 
 int /*<<< orphan*/  hostap_set_roaming (TYPE_2__*) ; 
 int /*<<< orphan*/  hostap_set_word (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prism2_set_genericelement (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_siwauth(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_param *data, char *extra)
{
	struct hostap_interface *iface = netdev_priv(dev);
	local_info_t *local = iface->local;

	switch (data->flags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VERSION:
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		/*
		 * Host AP driver does not use these parameters and allows
		 * wpa_supplicant to control them internally.
		 */
		break;
	case IW_AUTH_TKIP_COUNTERMEASURES:
		local->tkip_countermeasures = data->value;
		break;
	case IW_AUTH_DROP_UNENCRYPTED:
		local->drop_unencrypted = data->value;
		break;
	case IW_AUTH_80211_AUTH_ALG:
		local->auth_algs = data->value;
		break;
	case IW_AUTH_WPA_ENABLED:
		if (data->value == 0) {
			local->wpa = 0;
			if (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
				break;
			prism2_set_genericelement(dev, "", 0);
			local->host_roaming = 0;
			local->privacy_invoked = 0;
			if (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE,
					    0) ||
			    hostap_set_roaming(local) ||
			    hostap_set_encryption(local) ||
			    local->func->reset_port(dev))
				return -EINVAL;
			break;
		}
		if (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			return -EOPNOTSUPP;
		local->host_roaming = 2;
		local->privacy_invoked = 1;
		local->wpa = 1;
		if (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE, 1) ||
		    hostap_set_roaming(local) ||
		    hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			return -EINVAL;
		break;
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		local->ieee_802_1x = data->value;
		break;
	case IW_AUTH_PRIVACY_INVOKED:
		local->privacy_invoked = data->value;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}