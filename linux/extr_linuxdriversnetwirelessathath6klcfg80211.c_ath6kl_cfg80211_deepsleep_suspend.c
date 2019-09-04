#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {TYPE_1__* wmi; int /*<<< orphan*/  flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  pwr_mode; int /*<<< orphan*/  saved_pwr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_WOW_MODE_DISABLE ; 
 int EIO ; 
 int /*<<< orphan*/  REC_POWER ; 
 int /*<<< orphan*/  WMI_READY ; 
 int ath6kl_cfg80211_host_sleep (struct ath6kl*,struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_stop_all (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  ath6kl_tx_data_cleanup (struct ath6kl*) ; 
 struct ath6kl_vif* ath6kl_vif_first (struct ath6kl*) ; 
 int ath6kl_wmi_powermode_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_wow_mode_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_cfg80211_deepsleep_suspend(struct ath6kl *ar)
{
	struct ath6kl_vif *vif;
	int ret;

	vif = ath6kl_vif_first(ar);
	if (!vif)
		return -EIO;

	if (!test_bit(WMI_READY, &ar->flag)) {
		ath6kl_err("deepsleep failed as wmi is not ready\n");
		return -EIO;
	}

	ath6kl_cfg80211_stop_all(ar);

	/* Save the current power mode before enabling power save */
	ar->wmi->saved_pwr_mode = ar->wmi->pwr_mode;

	ret = ath6kl_wmi_powermode_cmd(ar->wmi, 0, REC_POWER);
	if (ret)
		return ret;

	/* Disable WOW mode */
	ret = ath6kl_wmi_set_wow_mode_cmd(ar->wmi, vif->fw_vif_idx,
					  ATH6KL_WOW_MODE_DISABLE,
					  0, 0);
	if (ret)
		return ret;

	/* Flush all non control pkts in TX path */
	ath6kl_tx_data_cleanup(ar);

	ret = ath6kl_cfg80211_host_sleep(ar, vif);
	if (ret)
		return ret;

	return 0;
}