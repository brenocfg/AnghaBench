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
struct ufs_pa_layer_attr {int /*<<< orphan*/  hs_rate; int /*<<< orphan*/  pwr_rx; int /*<<< orphan*/  gear_rx; } ;
struct ufs_qcom_host {struct ufs_pa_layer_attr dev_req_params; } ;
struct ufs_hba {int dummy; } ;
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;

/* Variables and functions */
 int PRE_CHANGE ; 
 int /*<<< orphan*/  ufs_qcom_cfg_timers (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ufs_qcom_clk_scale_down_post_change (struct ufs_hba*) ; 
 int ufs_qcom_clk_scale_down_pre_change (struct ufs_hba*) ; 
 int ufs_qcom_clk_scale_up_post_change (struct ufs_hba*) ; 
 int ufs_qcom_clk_scale_up_pre_change (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufs_qcom_update_bus_bw_vote (struct ufs_qcom_host*) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_qcom_clk_scale_notify(struct ufs_hba *hba,
		bool scale_up, enum ufs_notify_change_status status)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);
	struct ufs_pa_layer_attr *dev_req_params = &host->dev_req_params;
	int err = 0;

	if (status == PRE_CHANGE) {
		if (scale_up)
			err = ufs_qcom_clk_scale_up_pre_change(hba);
		else
			err = ufs_qcom_clk_scale_down_pre_change(hba);
	} else {
		if (scale_up)
			err = ufs_qcom_clk_scale_up_post_change(hba);
		else
			err = ufs_qcom_clk_scale_down_post_change(hba);

		if (err || !dev_req_params)
			goto out;

		ufs_qcom_cfg_timers(hba,
				    dev_req_params->gear_rx,
				    dev_req_params->pwr_rx,
				    dev_req_params->hs_rate,
				    false);
		ufs_qcom_update_bus_bw_vote(host);
	}

out:
	return err;
}