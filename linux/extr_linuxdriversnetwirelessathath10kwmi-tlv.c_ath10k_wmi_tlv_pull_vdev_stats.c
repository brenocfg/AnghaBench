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
struct wmi_tlv_vdev_stats {int /*<<< orphan*/ * beacon_rssi_history; int /*<<< orphan*/ * tx_rate_history; int /*<<< orphan*/ * num_tx_frames_failures; int /*<<< orphan*/ * num_tx_frames_retries; int /*<<< orphan*/ * num_tx_frames; int /*<<< orphan*/  num_tx_not_acked; int /*<<< orphan*/  num_rx_discard; int /*<<< orphan*/  num_rx_err; int /*<<< orphan*/  num_rts_success; int /*<<< orphan*/  num_rts_fail; int /*<<< orphan*/  num_rx_frames; int /*<<< orphan*/  data_snr; int /*<<< orphan*/  beacon_snr; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_fw_stats_vdev {void** beacon_rssi_history; void** tx_rate_history; void** num_tx_frames_failures; void** num_tx_frames_retries; void** num_tx_frames; void* num_tx_not_acked; void* num_rx_discard; void* num_rx_err; void* num_rts_success; void* num_rts_fail; void* num_rx_frames; void* data_snr; void* beacon_snr; void* vdev_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_wmi_tlv_pull_vdev_stats(const struct wmi_tlv_vdev_stats *src,
					   struct ath10k_fw_stats_vdev *dst)
{
	int i;

	dst->vdev_id = __le32_to_cpu(src->vdev_id);
	dst->beacon_snr = __le32_to_cpu(src->beacon_snr);
	dst->data_snr = __le32_to_cpu(src->data_snr);
	dst->num_rx_frames = __le32_to_cpu(src->num_rx_frames);
	dst->num_rts_fail = __le32_to_cpu(src->num_rts_fail);
	dst->num_rts_success = __le32_to_cpu(src->num_rts_success);
	dst->num_rx_err = __le32_to_cpu(src->num_rx_err);
	dst->num_rx_discard = __le32_to_cpu(src->num_rx_discard);
	dst->num_tx_not_acked = __le32_to_cpu(src->num_tx_not_acked);

	for (i = 0; i < ARRAY_SIZE(src->num_tx_frames); i++)
		dst->num_tx_frames[i] =
			__le32_to_cpu(src->num_tx_frames[i]);

	for (i = 0; i < ARRAY_SIZE(src->num_tx_frames_retries); i++)
		dst->num_tx_frames_retries[i] =
			__le32_to_cpu(src->num_tx_frames_retries[i]);

	for (i = 0; i < ARRAY_SIZE(src->num_tx_frames_failures); i++)
		dst->num_tx_frames_failures[i] =
			__le32_to_cpu(src->num_tx_frames_failures[i]);

	for (i = 0; i < ARRAY_SIZE(src->tx_rate_history); i++)
		dst->tx_rate_history[i] =
			__le32_to_cpu(src->tx_rate_history[i]);

	for (i = 0; i < ARRAY_SIZE(src->beacon_rssi_history); i++)
		dst->beacon_rssi_history[i] =
			__le32_to_cpu(src->beacon_rssi_history[i]);
}