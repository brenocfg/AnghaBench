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
struct ath10k_htt {int prefetch_len; int /*<<< orphan*/  t2h_msg_types_max; int /*<<< orphan*/  t2h_msg_types; struct ath10k* ar; } ;
struct ath10k {struct ath10k_htt htt; TYPE_2__* running_fw; } ;
struct TYPE_3__ {int htt_op_version; } ;
struct TYPE_4__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
#define  ATH10K_FW_HTT_OP_VERSION_10_1 133 
#define  ATH10K_FW_HTT_OP_VERSION_10_4 132 
#define  ATH10K_FW_HTT_OP_VERSION_MAIN 131 
#define  ATH10K_FW_HTT_OP_VERSION_MAX 130 
#define  ATH10K_FW_HTT_OP_VERSION_TLV 129 
#define  ATH10K_FW_HTT_OP_VERSION_UNSET 128 
 int EINVAL ; 
 int /*<<< orphan*/  HTT_10X_T2H_NUM_MSGS ; 
 int /*<<< orphan*/  HTT_10_4_T2H_NUM_MSGS ; 
 int /*<<< orphan*/  HTT_MAIN_T2H_NUM_MSGS ; 
 int /*<<< orphan*/  HTT_TLV_T2H_NUM_MSGS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_htt_set_rx_ops (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_set_tx_ops (struct ath10k_htt*) ; 
 int /*<<< orphan*/  htt_10_4_t2h_msg_types ; 
 int /*<<< orphan*/  htt_10x_t2h_msg_types ; 
 int /*<<< orphan*/  htt_main_t2h_msg_types ; 
 int /*<<< orphan*/  htt_tlv_t2h_msg_types ; 

int ath10k_htt_init(struct ath10k *ar)
{
	struct ath10k_htt *htt = &ar->htt;

	htt->ar = ar;

	/*
	 * Prefetch enough data to satisfy target
	 * classification engine.
	 * This is for LL chips. HL chips will probably
	 * transfer all frame in the tx fragment.
	 */
	htt->prefetch_len =
		36 + /* 802.11 + qos + ht */
		4 + /* 802.1q */
		8 + /* llc snap */
		2; /* ip4 dscp or ip6 priority */

	switch (ar->running_fw->fw_file.htt_op_version) {
	case ATH10K_FW_HTT_OP_VERSION_10_4:
		ar->htt.t2h_msg_types = htt_10_4_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_10_4_T2H_NUM_MSGS;
		break;
	case ATH10K_FW_HTT_OP_VERSION_10_1:
		ar->htt.t2h_msg_types = htt_10x_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_10X_T2H_NUM_MSGS;
		break;
	case ATH10K_FW_HTT_OP_VERSION_TLV:
		ar->htt.t2h_msg_types = htt_tlv_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_TLV_T2H_NUM_MSGS;
		break;
	case ATH10K_FW_HTT_OP_VERSION_MAIN:
		ar->htt.t2h_msg_types = htt_main_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_MAIN_T2H_NUM_MSGS;
		break;
	case ATH10K_FW_HTT_OP_VERSION_MAX:
	case ATH10K_FW_HTT_OP_VERSION_UNSET:
		WARN_ON(1);
		return -EINVAL;
	}
	ath10k_htt_set_tx_ops(htt);
	ath10k_htt_set_rx_ops(htt);

	return 0;
}