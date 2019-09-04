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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_data; } ;
struct iw_mlme {int cmd; TYPE_1__ addr; int /*<<< orphan*/  reason_code; } ;
struct hostap_interface {int /*<<< orphan*/ * local; } ;
typedef  int /*<<< orphan*/  local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DISASSOC ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int prism2_sta_send_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int prism2_ioctl_siwmlme(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_point *data, char *extra)
{
	struct hostap_interface *iface = netdev_priv(dev);
	local_info_t *local = iface->local;
	struct iw_mlme *mlme = (struct iw_mlme *) extra;
	__le16 reason;

	reason = cpu_to_le16(mlme->reason_code);

	switch (mlme->cmd) {
	case IW_MLME_DEAUTH:
		return prism2_sta_send_mgmt(local, mlme->addr.sa_data,
					    IEEE80211_STYPE_DEAUTH,
					    (u8 *) &reason, 2);
	case IW_MLME_DISASSOC:
		return prism2_sta_send_mgmt(local, mlme->addr.sa_data,
					    IEEE80211_STYPE_DISASSOC,
					    (u8 *) &reason, 2);
	default:
		return -EOPNOTSUPP;
	}
}