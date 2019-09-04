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
typedef  int u32 ;
struct il_sensitivity_ranges {scalar_t__ auto_corr_min_ofdm_mrc_x1; scalar_t__ auto_corr_min_ofdm_x1; scalar_t__ auto_corr_min_ofdm_mrc; scalar_t__ auto_corr_min_ofdm; scalar_t__ auto_corr_max_ofdm_mrc_x1; scalar_t__ auto_corr_max_ofdm_x1; scalar_t__ auto_corr_max_ofdm_mrc; scalar_t__ auto_corr_max_ofdm; } ;
struct il_sensitivity_data {int auto_corr_ofdm; int auto_corr_ofdm_mrc; int auto_corr_ofdm_x1; int auto_corr_ofdm_mrc_x1; } ;
struct TYPE_2__ {struct il_sensitivity_ranges* sens; } ;
struct il_priv {struct il_sensitivity_data sensitivity_data; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int AUTO_CORR_STEP_OFDM ; 
 int /*<<< orphan*/  D_CALIB (char*,int,int,...) ; 
 int MAX_FA_OFDM ; 
 int MIN_FA_OFDM ; 
 void* max (int,int) ; 
 void* min (int,int) ; 

__attribute__((used)) static int
il4965_sens_auto_corr_ofdm(struct il_priv *il, u32 norm_fa, u32 rx_enable_time)
{
	u32 val;
	u32 false_alarms = norm_fa * 200 * 1024;
	u32 max_false_alarms = MAX_FA_OFDM * rx_enable_time;
	u32 min_false_alarms = MIN_FA_OFDM * rx_enable_time;
	struct il_sensitivity_data *data = NULL;
	const struct il_sensitivity_ranges *ranges = il->hw_params.sens;

	data = &(il->sensitivity_data);

	/* If we got too many false alarms this time, reduce sensitivity */
	if (false_alarms > max_false_alarms) {

		D_CALIB("norm FA %u > max FA %u)\n", false_alarms,
			max_false_alarms);

		val = data->auto_corr_ofdm + AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm =
		    min((u32) ranges->auto_corr_max_ofdm, val);

		val = data->auto_corr_ofdm_mrc + AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_mrc =
		    min((u32) ranges->auto_corr_max_ofdm_mrc, val);

		val = data->auto_corr_ofdm_x1 + AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_x1 =
		    min((u32) ranges->auto_corr_max_ofdm_x1, val);

		val = data->auto_corr_ofdm_mrc_x1 + AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_mrc_x1 =
		    min((u32) ranges->auto_corr_max_ofdm_mrc_x1, val);
	}

	/* Else if we got fewer than desired, increase sensitivity */
	else if (false_alarms < min_false_alarms) {

		D_CALIB("norm FA %u < min FA %u\n", false_alarms,
			min_false_alarms);

		val = data->auto_corr_ofdm - AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm =
		    max((u32) ranges->auto_corr_min_ofdm, val);

		val = data->auto_corr_ofdm_mrc - AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_mrc =
		    max((u32) ranges->auto_corr_min_ofdm_mrc, val);

		val = data->auto_corr_ofdm_x1 - AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_x1 =
		    max((u32) ranges->auto_corr_min_ofdm_x1, val);

		val = data->auto_corr_ofdm_mrc_x1 - AUTO_CORR_STEP_OFDM;
		data->auto_corr_ofdm_mrc_x1 =
		    max((u32) ranges->auto_corr_min_ofdm_mrc_x1, val);
	} else {
		D_CALIB("min FA %u < norm FA %u < max FA %u OK\n",
			min_false_alarms, false_alarms, max_false_alarms);
	}
	return 0;
}