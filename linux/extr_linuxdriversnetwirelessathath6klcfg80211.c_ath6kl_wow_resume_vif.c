#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  ndev; int /*<<< orphan*/  fw_vif_idx; struct ath6kl* ar; int /*<<< orphan*/  flags; int /*<<< orphan*/  bmiss_time_t; int /*<<< orphan*/  listen_intvl_t; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/ * fw_capabilities; } ;

/* Variables and functions */
 scalar_t__ AP_NETWORK ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER ; 
 int /*<<< orphan*/  NETDEV_MCAST_ALL_OFF ; 
 int ath6kl_wmi_bmisstime_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_listeninterval_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_mcast_filter_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ath6kl_wmi_scanparams_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_wow_resume_vif(struct ath6kl_vif *vif)
{
	struct ath6kl *ar = vif->ar;
	int ret;

	if (vif->nw_type != AP_NETWORK) {
		ret = ath6kl_wmi_scanparams_cmd(ar->wmi, vif->fw_vif_idx,
						0, 0, 0, 0, 0, 0, 3, 0, 0, 0);
		if (ret)
			return ret;

		ret = ath6kl_wmi_listeninterval_cmd(ar->wmi, vif->fw_vif_idx,
						    vif->listen_intvl_t, 0);
		if (ret)
			return ret;

		ret = ath6kl_wmi_bmisstime_cmd(ar->wmi, vif->fw_vif_idx,
					       vif->bmiss_time_t, 0);
		if (ret)
			return ret;
	}

	if (!test_bit(NETDEV_MCAST_ALL_OFF, &vif->flags) &&
	    test_bit(ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER,
		     ar->fw_capabilities)) {
		ret = ath6kl_wmi_mcast_filter_cmd(vif->ar->wmi,
						  vif->fw_vif_idx, true);
		if (ret)
			return ret;
	}

	netif_wake_queue(vif->ndev);

	return 0;
}