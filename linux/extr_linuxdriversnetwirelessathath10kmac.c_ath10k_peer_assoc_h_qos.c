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
struct wmi_peer_assoc_complete_arg {int peer_flags; int /*<<< orphan*/  peer_rate_caps; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; int /*<<< orphan*/  wme; int /*<<< orphan*/  uapsd_queues; } ;
struct ath10k_vif {int vdev_type; TYPE_3__* ar; } ;
struct ath10k {int dummy; } ;
struct TYPE_5__ {TYPE_1__* peer_flags; } ;
struct TYPE_6__ {TYPE_2__ wmi; } ;
struct TYPE_4__ {int qos; int apsd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  WMI_RC_UAPSD_FLAG ; 
#define  WMI_VDEV_TYPE_AP 130 
#define  WMI_VDEV_TYPE_IBSS 129 
#define  WMI_VDEV_TYPE_STA 128 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath10k_peer_assoc_h_qos(struct ath10k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct wmi_peer_assoc_complete_arg *arg)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;

	switch (arvif->vdev_type) {
	case WMI_VDEV_TYPE_AP:
		if (sta->wme)
			arg->peer_flags |= arvif->ar->wmi.peer_flags->qos;

		if (sta->wme && sta->uapsd_queues) {
			arg->peer_flags |= arvif->ar->wmi.peer_flags->apsd;
			arg->peer_rate_caps |= WMI_RC_UAPSD_FLAG;
		}
		break;
	case WMI_VDEV_TYPE_STA:
		if (sta->wme)
			arg->peer_flags |= arvif->ar->wmi.peer_flags->qos;
		break;
	case WMI_VDEV_TYPE_IBSS:
		if (sta->wme)
			arg->peer_flags |= arvif->ar->wmi.peer_flags->qos;
		break;
	default:
		break;
	}

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac peer %pM qos %d\n",
		   sta->addr, !!(arg->peer_flags &
		   arvif->ar->wmi.peer_flags->qos));
}