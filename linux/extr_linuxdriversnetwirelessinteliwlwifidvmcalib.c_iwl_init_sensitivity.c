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
struct iwl_sensitivity_ranges {int /*<<< orphan*/  nrg_th_cca; int /*<<< orphan*/  barker_corr_th_min_mrc; int /*<<< orphan*/  barker_corr_th_min; int /*<<< orphan*/  nrg_th_ofdm; int /*<<< orphan*/  nrg_th_cck; int /*<<< orphan*/  auto_corr_min_cck_mrc; int /*<<< orphan*/  auto_corr_min_ofdm_mrc_x1; int /*<<< orphan*/  auto_corr_min_ofdm_x1; int /*<<< orphan*/  auto_corr_min_ofdm_mrc; int /*<<< orphan*/  auto_corr_min_ofdm; } ;
struct iwl_sensitivity_data {scalar_t__ last_fa_cnt_cck; scalar_t__ last_bad_plcp_cnt_cck; scalar_t__ last_fa_cnt_ofdm; scalar_t__ last_bad_plcp_cnt_ofdm; int /*<<< orphan*/  nrg_th_cca; int /*<<< orphan*/  barker_corr_th_min_mrc; int /*<<< orphan*/  barker_corr_th_min; int /*<<< orphan*/  nrg_th_ofdm; int /*<<< orphan*/  nrg_th_cck; int /*<<< orphan*/  auto_corr_cck_mrc; int /*<<< orphan*/  auto_corr_cck; int /*<<< orphan*/  auto_corr_ofdm_mrc_x1; int /*<<< orphan*/  auto_corr_ofdm_x1; int /*<<< orphan*/  auto_corr_ofdm_mrc; int /*<<< orphan*/  auto_corr_ofdm; scalar_t__* nrg_silence_rssi; scalar_t__* nrg_value; scalar_t__ nrg_energy_idx; scalar_t__ nrg_silence_idx; scalar_t__ nrg_silence_ref; void* nrg_prev_state; void* nrg_curr_state; scalar_t__ num_in_cck_no_fa; } ;
struct TYPE_3__ {struct iwl_sensitivity_ranges* sens; } ;
struct iwl_priv {int calib_disabled; TYPE_2__* fw; struct iwl_sensitivity_data sensitivity_data; TYPE_1__ hw_params; } ;
struct TYPE_4__ {scalar_t__ enhance_sensitivity_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_CORR_CCK_MIN_VAL_DEF ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,...) ; 
 void* IWL_FA_TOO_MANY ; 
 int IWL_SENSITIVITY_CALIB_DISABLED ; 
 int NRG_NUM_PREV_STAT_L ; 
 int iwl_enhance_sensitivity_write (struct iwl_priv*) ; 
 int iwl_sensitivity_write (struct iwl_priv*) ; 
 int /*<<< orphan*/  memset (struct iwl_sensitivity_data*,int /*<<< orphan*/ ,int) ; 

void iwl_init_sensitivity(struct iwl_priv *priv)
{
	int ret = 0;
	int i;
	struct iwl_sensitivity_data *data = NULL;
	const struct iwl_sensitivity_ranges *ranges = priv->hw_params.sens;

	if (priv->calib_disabled & IWL_SENSITIVITY_CALIB_DISABLED)
		return;

	IWL_DEBUG_CALIB(priv, "Start iwl_init_sensitivity\n");

	/* Clear driver's sensitivity algo data */
	data = &(priv->sensitivity_data);

	if (ranges == NULL)
		return;

	memset(data, 0, sizeof(struct iwl_sensitivity_data));

	data->num_in_cck_no_fa = 0;
	data->nrg_curr_state = IWL_FA_TOO_MANY;
	data->nrg_prev_state = IWL_FA_TOO_MANY;
	data->nrg_silence_ref = 0;
	data->nrg_silence_idx = 0;
	data->nrg_energy_idx = 0;

	for (i = 0; i < 10; i++)
		data->nrg_value[i] = 0;

	for (i = 0; i < NRG_NUM_PREV_STAT_L; i++)
		data->nrg_silence_rssi[i] = 0;

	data->auto_corr_ofdm =  ranges->auto_corr_min_ofdm;
	data->auto_corr_ofdm_mrc = ranges->auto_corr_min_ofdm_mrc;
	data->auto_corr_ofdm_x1  = ranges->auto_corr_min_ofdm_x1;
	data->auto_corr_ofdm_mrc_x1 = ranges->auto_corr_min_ofdm_mrc_x1;
	data->auto_corr_cck = AUTO_CORR_CCK_MIN_VAL_DEF;
	data->auto_corr_cck_mrc = ranges->auto_corr_min_cck_mrc;
	data->nrg_th_cck = ranges->nrg_th_cck;
	data->nrg_th_ofdm = ranges->nrg_th_ofdm;
	data->barker_corr_th_min = ranges->barker_corr_th_min;
	data->barker_corr_th_min_mrc = ranges->barker_corr_th_min_mrc;
	data->nrg_th_cca = ranges->nrg_th_cca;

	data->last_bad_plcp_cnt_ofdm = 0;
	data->last_fa_cnt_ofdm = 0;
	data->last_bad_plcp_cnt_cck = 0;
	data->last_fa_cnt_cck = 0;

	if (priv->fw->enhance_sensitivity_table)
		ret |= iwl_enhance_sensitivity_write(priv);
	else
		ret |= iwl_sensitivity_write(priv);
	IWL_DEBUG_CALIB(priv, "<<return 0x%X\n", ret);
}