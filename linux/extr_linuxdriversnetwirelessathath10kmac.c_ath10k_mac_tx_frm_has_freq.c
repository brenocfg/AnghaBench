#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int target_version_major; int target_version_minor; } ;
struct ath10k {TYPE_3__* running_fw; TYPE_1__ htt; } ;
struct TYPE_5__ {scalar_t__ htt_op_version; } ;
struct TYPE_6__ {TYPE_2__ fw_file; } ;

/* Variables and functions */
 scalar_t__ ATH10K_FW_HTT_OP_VERSION_TLV ; 

bool ath10k_mac_tx_frm_has_freq(struct ath10k *ar)
{
	/* FIXME: Not really sure since when the behaviour changed. At some
	 * point new firmware stopped requiring creation of peer entries for
	 * offchannel tx (and actually creating them causes issues with wmi-htc
	 * tx credit replenishment and reliability). Assuming it's at least 3.4
	 * because that's when the `freq` was introduced to TX_FRM HTT command.
	 */
	return (ar->htt.target_version_major >= 3 &&
		ar->htt.target_version_minor >= 4 &&
		ar->running_fw->fw_file.htt_op_version == ATH10K_FW_HTT_OP_VERSION_TLV);
}