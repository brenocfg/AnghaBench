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
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  fw_vif_idx; TYPE_1__* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  wmi; int /*<<< orphan*/ * fw_capabilities; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WLAN_CFG ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_BMISS_ENHANCE ; 
 scalar_t__ INFRA_NETWORK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_READY ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ath6kl_err (char*,char*,int) ; 
 int ath6kl_wmi_sta_bmiss_enhance_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_cfg80211_sta_bmiss_enhance(struct ath6kl_vif *vif,
					      bool enable)
{
	int err;

	if (WARN_ON(!test_bit(WMI_READY, &vif->ar->flag)))
		return;

	if (vif->nw_type != INFRA_NETWORK)
		return;

	if (!test_bit(ATH6KL_FW_CAPABILITY_BMISS_ENHANCE,
		      vif->ar->fw_capabilities))
		return;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s fw bmiss enhance\n",
		   enable ? "enable" : "disable");

	err = ath6kl_wmi_sta_bmiss_enhance_cmd(vif->ar->wmi,
					       vif->fw_vif_idx, enable);
	if (err)
		ath6kl_err("failed to %s enhanced bmiss detection: %d\n",
			   enable ? "enable" : "disable", err);
}