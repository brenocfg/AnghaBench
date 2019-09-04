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
struct wmi_vdev_spectral_conf_cmd {void* scan_chn_mask; void* scan_dbm_adj; void* scan_bin_scale; void* scan_rpt_mode; void* scan_pwr_format; void* scan_rssi_thr; void* scan_rssi_rpt_mode; void* scan_wb_rpt_mode; void* scan_str_bin_thr; void* scan_nb_tone_thr; void* scan_init_delay; void* scan_noise_floor_ref; void* scan_restart_ena; void* scan_gc_ena; void* scan_fft_size; void* scan_priority; void* scan_period; void* scan_count; void* vdev_id; } ;
struct wmi_vdev_spectral_conf_arg {int /*<<< orphan*/  scan_chn_mask; int /*<<< orphan*/  scan_dbm_adj; int /*<<< orphan*/  scan_bin_scale; int /*<<< orphan*/  scan_rpt_mode; int /*<<< orphan*/  scan_pwr_format; int /*<<< orphan*/  scan_rssi_thr; int /*<<< orphan*/  scan_rssi_rpt_mode; int /*<<< orphan*/  scan_wb_rpt_mode; int /*<<< orphan*/  scan_str_bin_thr; int /*<<< orphan*/  scan_nb_tone_thr; int /*<<< orphan*/  scan_init_delay; int /*<<< orphan*/  scan_noise_floor_ref; int /*<<< orphan*/  scan_restart_ena; int /*<<< orphan*/  scan_gc_ena; int /*<<< orphan*/  scan_fft_size; int /*<<< orphan*/  scan_priority; int /*<<< orphan*/  scan_period; int /*<<< orphan*/  scan_count; int /*<<< orphan*/  vdev_id; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_vdev_spectral_conf(struct ath10k *ar,
				     const struct wmi_vdev_spectral_conf_arg *arg)
{
	struct wmi_vdev_spectral_conf_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_vdev_spectral_conf_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->scan_count = __cpu_to_le32(arg->scan_count);
	cmd->scan_period = __cpu_to_le32(arg->scan_period);
	cmd->scan_priority = __cpu_to_le32(arg->scan_priority);
	cmd->scan_fft_size = __cpu_to_le32(arg->scan_fft_size);
	cmd->scan_gc_ena = __cpu_to_le32(arg->scan_gc_ena);
	cmd->scan_restart_ena = __cpu_to_le32(arg->scan_restart_ena);
	cmd->scan_noise_floor_ref = __cpu_to_le32(arg->scan_noise_floor_ref);
	cmd->scan_init_delay = __cpu_to_le32(arg->scan_init_delay);
	cmd->scan_nb_tone_thr = __cpu_to_le32(arg->scan_nb_tone_thr);
	cmd->scan_str_bin_thr = __cpu_to_le32(arg->scan_str_bin_thr);
	cmd->scan_wb_rpt_mode = __cpu_to_le32(arg->scan_wb_rpt_mode);
	cmd->scan_rssi_rpt_mode = __cpu_to_le32(arg->scan_rssi_rpt_mode);
	cmd->scan_rssi_thr = __cpu_to_le32(arg->scan_rssi_thr);
	cmd->scan_pwr_format = __cpu_to_le32(arg->scan_pwr_format);
	cmd->scan_rpt_mode = __cpu_to_le32(arg->scan_rpt_mode);
	cmd->scan_bin_scale = __cpu_to_le32(arg->scan_bin_scale);
	cmd->scan_dbm_adj = __cpu_to_le32(arg->scan_dbm_adj);
	cmd->scan_chn_mask = __cpu_to_le32(arg->scan_chn_mask);

	return skb;
}