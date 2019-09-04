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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int /*<<< orphan*/  value; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  ieee_802_1x; int /*<<< orphan*/  wpa; int /*<<< orphan*/  auth_algs; int /*<<< orphan*/  drop_unencrypted; int /*<<< orphan*/  tkip_countermeasures; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
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
 struct hostap_interface* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_giwauth(struct net_device *dev,
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
		return -EOPNOTSUPP;
	case IW_AUTH_TKIP_COUNTERMEASURES:
		data->value = local->tkip_countermeasures;
		break;
	case IW_AUTH_DROP_UNENCRYPTED:
		data->value = local->drop_unencrypted;
		break;
	case IW_AUTH_80211_AUTH_ALG:
		data->value = local->auth_algs;
		break;
	case IW_AUTH_WPA_ENABLED:
		data->value = local->wpa;
		break;
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		data->value = local->ieee_802_1x;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}