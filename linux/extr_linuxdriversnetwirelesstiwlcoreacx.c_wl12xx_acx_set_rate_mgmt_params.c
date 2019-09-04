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
struct wl12xx_acx_set_rate_mgmt_params {int /*<<< orphan*/  rate_retry_policy; int /*<<< orphan*/  rate_check_down; int /*<<< orphan*/  rate_check_up; int /*<<< orphan*/  per_beta2_shift; int /*<<< orphan*/  per_beta1_shift; int /*<<< orphan*/  per_add_shift; int /*<<< orphan*/  per_alpha_shift; int /*<<< orphan*/  tx_fail_high_th; int /*<<< orphan*/  tx_fail_low_th; int /*<<< orphan*/  inverse_curiosity_factor; void* max_per; void* per_th2; void* per_th1; void* per_add; void* rate_retry_score; int /*<<< orphan*/  index; } ;
struct conf_rate_policy_settings {int /*<<< orphan*/  rate_retry_policy; int /*<<< orphan*/  rate_check_down; int /*<<< orphan*/  rate_check_up; int /*<<< orphan*/  per_beta2_shift; int /*<<< orphan*/  per_beta1_shift; int /*<<< orphan*/  per_add_shift; int /*<<< orphan*/  per_alpha_shift; int /*<<< orphan*/  tx_fail_high_th; int /*<<< orphan*/  tx_fail_low_th; int /*<<< orphan*/  inverse_curiosity_factor; int /*<<< orphan*/  max_per; int /*<<< orphan*/  per_th2; int /*<<< orphan*/  per_th1; int /*<<< orphan*/  per_add; int /*<<< orphan*/  rate_retry_score; } ;
struct TYPE_2__ {struct conf_rate_policy_settings rate; } ;
struct wl1271 {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_RATE_MGMT_ALL_PARAMS ; 
 int /*<<< orphan*/  ACX_SET_RATE_MGMT_PARAMS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_acx_set_rate_mgmt_params*) ; 
 struct wl12xx_acx_set_rate_mgmt_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_acx_set_rate_mgmt_params*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl12xx_acx_set_rate_mgmt_params(struct wl1271 *wl)
{
	struct wl12xx_acx_set_rate_mgmt_params *acx = NULL;
	struct conf_rate_policy_settings *conf = &wl->conf.rate;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx set rate mgmt params");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->index = ACX_RATE_MGMT_ALL_PARAMS;
	acx->rate_retry_score = cpu_to_le16(conf->rate_retry_score);
	acx->per_add = cpu_to_le16(conf->per_add);
	acx->per_th1 = cpu_to_le16(conf->per_th1);
	acx->per_th2 = cpu_to_le16(conf->per_th2);
	acx->max_per = cpu_to_le16(conf->max_per);
	acx->inverse_curiosity_factor = conf->inverse_curiosity_factor;
	acx->tx_fail_low_th = conf->tx_fail_low_th;
	acx->tx_fail_high_th = conf->tx_fail_high_th;
	acx->per_alpha_shift = conf->per_alpha_shift;
	acx->per_add_shift = conf->per_add_shift;
	acx->per_beta1_shift = conf->per_beta1_shift;
	acx->per_beta2_shift = conf->per_beta2_shift;
	acx->rate_check_up = conf->rate_check_up;
	acx->rate_check_down = conf->rate_check_down;
	memcpy(acx->rate_retry_policy, conf->rate_retry_policy,
	       sizeof(acx->rate_retry_policy));

	ret = wl1271_cmd_configure(wl, ACX_SET_RATE_MGMT_PARAMS,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx set rate mgmt params failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}