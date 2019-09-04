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
struct wmi_vdev_spectral_conf_arg {int vdev_id; int scan_count; int /*<<< orphan*/  scan_chn_mask; int /*<<< orphan*/  scan_dbm_adj; int /*<<< orphan*/  scan_bin_scale; int /*<<< orphan*/  scan_rpt_mode; int /*<<< orphan*/  scan_pwr_format; int /*<<< orphan*/  scan_rssi_thr; int /*<<< orphan*/  scan_rssi_rpt_mode; int /*<<< orphan*/  scan_wb_rpt_mode; int /*<<< orphan*/  scan_str_bin_thr; int /*<<< orphan*/  scan_nb_tone_thr; int /*<<< orphan*/  scan_init_delay; int /*<<< orphan*/  scan_noise_floor_ref; int /*<<< orphan*/  scan_restart_ena; int /*<<< orphan*/  scan_gc_ena; int /*<<< orphan*/  scan_fft_size; int /*<<< orphan*/  scan_priority; int /*<<< orphan*/  scan_period; } ;
struct ath10k_vif {int vdev_id; int spectral_enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  fft_size; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int mode; TYPE_1__ config; } ;
struct ath10k {TYPE_2__ spectral; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum ath10k_spectral_mode { ____Placeholder_ath10k_spectral_mode } ath10k_spectral_mode ;

/* Variables and functions */
 int ENODEV ; 
 int SPECTRAL_BACKGROUND ; 
 int SPECTRAL_DISABLED ; 
 int /*<<< orphan*/  WMI_SPECTRAL_BIN_SCALE_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_CHN_MASK_DEFAULT ; 
 int WMI_SPECTRAL_COUNT_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_DBM_ADJ_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_ENABLE_CMD_DISABLE ; 
 int /*<<< orphan*/  WMI_SPECTRAL_GC_ENA_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_INIT_DELAY_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_NB_TONE_THR_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_NOISE_FLOOR_REF_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_PERIOD_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_PRIORITY_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_PWR_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_RESTART_ENA_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_RPT_MODE_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_RSSI_RPT_MODE_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_RSSI_THR_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_STR_BIN_THR_DEFAULT ; 
 int /*<<< orphan*/  WMI_SPECTRAL_TRIGGER_CMD_CLEAR ; 
 int /*<<< orphan*/  WMI_SPECTRAL_WB_RPT_MODE_DEFAULT ; 
 struct ath10k_vif* ath10k_get_spectral_vdev (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_vdev_spectral_conf (struct ath10k*,struct wmi_vdev_spectral_conf_arg*) ; 
 int ath10k_wmi_vdev_spectral_enable (struct ath10k*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static int ath10k_spectral_scan_config(struct ath10k *ar,
				       enum ath10k_spectral_mode mode)
{
	struct wmi_vdev_spectral_conf_arg arg;
	struct ath10k_vif *arvif;
	int vdev_id, count, res = 0;

	lockdep_assert_held(&ar->conf_mutex);

	arvif = ath10k_get_spectral_vdev(ar);
	if (!arvif)
		return -ENODEV;

	vdev_id = arvif->vdev_id;

	arvif->spectral_enabled = (mode != SPECTRAL_DISABLED);
	ar->spectral.mode = mode;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      WMI_SPECTRAL_ENABLE_CMD_DISABLE);
	if (res < 0) {
		ath10k_warn(ar, "failed to enable spectral scan: %d\n", res);
		return res;
	}

	if (mode == SPECTRAL_DISABLED)
		return 0;

	if (mode == SPECTRAL_BACKGROUND)
		count = WMI_SPECTRAL_COUNT_DEFAULT;
	else
		count = max_t(u8, 1, ar->spectral.config.count);

	arg.vdev_id = vdev_id;
	arg.scan_count = count;
	arg.scan_period = WMI_SPECTRAL_PERIOD_DEFAULT;
	arg.scan_priority = WMI_SPECTRAL_PRIORITY_DEFAULT;
	arg.scan_fft_size = ar->spectral.config.fft_size;
	arg.scan_gc_ena = WMI_SPECTRAL_GC_ENA_DEFAULT;
	arg.scan_restart_ena = WMI_SPECTRAL_RESTART_ENA_DEFAULT;
	arg.scan_noise_floor_ref = WMI_SPECTRAL_NOISE_FLOOR_REF_DEFAULT;
	arg.scan_init_delay = WMI_SPECTRAL_INIT_DELAY_DEFAULT;
	arg.scan_nb_tone_thr = WMI_SPECTRAL_NB_TONE_THR_DEFAULT;
	arg.scan_str_bin_thr = WMI_SPECTRAL_STR_BIN_THR_DEFAULT;
	arg.scan_wb_rpt_mode = WMI_SPECTRAL_WB_RPT_MODE_DEFAULT;
	arg.scan_rssi_rpt_mode = WMI_SPECTRAL_RSSI_RPT_MODE_DEFAULT;
	arg.scan_rssi_thr = WMI_SPECTRAL_RSSI_THR_DEFAULT;
	arg.scan_pwr_format = WMI_SPECTRAL_PWR_FORMAT_DEFAULT;
	arg.scan_rpt_mode = WMI_SPECTRAL_RPT_MODE_DEFAULT;
	arg.scan_bin_scale = WMI_SPECTRAL_BIN_SCALE_DEFAULT;
	arg.scan_dbm_adj = WMI_SPECTRAL_DBM_ADJ_DEFAULT;
	arg.scan_chn_mask = WMI_SPECTRAL_CHN_MASK_DEFAULT;

	res = ath10k_wmi_vdev_spectral_conf(ar, &arg);
	if (res < 0) {
		ath10k_warn(ar, "failed to configure spectral scan: %d\n", res);
		return res;
	}

	return 0;
}