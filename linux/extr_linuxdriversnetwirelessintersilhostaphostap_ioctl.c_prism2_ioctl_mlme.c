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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  reason_code; } ;
struct TYPE_4__ {TYPE_1__ mlme; } ;
struct prism2_hostapd_param {int /*<<< orphan*/  sta_addr; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DISASSOC ; 
#define  MLME_STA_DEAUTH 129 
#define  MLME_STA_DISASSOC 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int prism2_sta_send_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int prism2_ioctl_mlme(local_info_t *local,
			     struct prism2_hostapd_param *param)
{
	__le16 reason;

	reason = cpu_to_le16(param->u.mlme.reason_code);
	switch (param->u.mlme.cmd) {
	case MLME_STA_DEAUTH:
		return prism2_sta_send_mgmt(local, param->sta_addr,
					    IEEE80211_STYPE_DEAUTH,
					    (u8 *) &reason, 2);
	case MLME_STA_DISASSOC:
		return prism2_sta_send_mgmt(local, param->sta_addr,
					    IEEE80211_STYPE_DISASSOC,
					    (u8 *) &reason, 2);
	default:
		return -EOPNOTSUPP;
	}
}