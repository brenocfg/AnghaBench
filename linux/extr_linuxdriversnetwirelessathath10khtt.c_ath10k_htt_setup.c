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
struct ath10k_htt {int /*<<< orphan*/  max_num_amsdu; int /*<<< orphan*/  max_num_ampdu; int /*<<< orphan*/  target_version_received; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HTT_TARGET_VERSION_TIMEOUT_HZ ; 
 int ath10k_htt_h2t_aggr_cfg_msg (struct ath10k_htt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_htt_h2t_ver_req_msg (struct ath10k_htt*) ; 
 int ath10k_htt_send_frag_desc_bank_cfg (struct ath10k_htt*) ; 
 int ath10k_htt_send_rx_ring_cfg (struct ath10k_htt*) ; 
 int ath10k_htt_verify_version (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ath10k_htt_setup(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;
	int status;

	init_completion(&htt->target_version_received);

	status = ath10k_htt_h2t_ver_req_msg(htt);
	if (status)
		return status;

	status = wait_for_completion_timeout(&htt->target_version_received,
					     HTT_TARGET_VERSION_TIMEOUT_HZ);
	if (status == 0) {
		ath10k_warn(ar, "htt version request timed out\n");
		return -ETIMEDOUT;
	}

	status = ath10k_htt_verify_version(htt);
	if (status) {
		ath10k_warn(ar, "failed to verify htt version: %d\n",
			    status);
		return status;
	}

	status = ath10k_htt_send_frag_desc_bank_cfg(htt);
	if (status)
		return status;

	status = ath10k_htt_send_rx_ring_cfg(htt);
	if (status) {
		ath10k_warn(ar, "failed to setup rx ring: %d\n",
			    status);
		return status;
	}

	status = ath10k_htt_h2t_aggr_cfg_msg(htt,
					     htt->max_num_ampdu,
					     htt->max_num_amsdu);
	if (status) {
		ath10k_warn(ar, "failed to setup amsdu/ampdu limit: %d\n",
			    status);
		return status;
	}

	return 0;
}