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
typedef  int /*<<< orphan*/  u8 ;
struct ath5k_txq_info {scalar_t__ tqi_type; scalar_t__ tqi_subtype; int /*<<< orphan*/  tqi_flags; int /*<<< orphan*/  tqi_ready_time; int /*<<< orphan*/  tqi_burst_time; int /*<<< orphan*/  tqi_cbr_overflow_limit; int /*<<< orphan*/  tqi_cbr_period; void* tqi_cw_max; void* tqi_cw_min; int /*<<< orphan*/  tqi_aifs; } ;
struct TYPE_3__ {int /*<<< orphan*/  q_tx_num; } ;
struct TYPE_4__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {struct ath5k_txq_info* ah_txq; TYPE_2__ ah_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_ASSERT_ENTRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_TXQ_FLAG_POST_FR_BKOFF_DIS ; 
 scalar_t__ AR5K_TX_QUEUE_DATA ; 
 scalar_t__ AR5K_TX_QUEUE_INACTIVE ; 
 scalar_t__ AR5K_TX_QUEUE_UAPSD ; 
 scalar_t__ AR5K_WME_AC_VI ; 
 scalar_t__ AR5K_WME_AC_VO ; 
 int EIO ; 
 void* ath5k_cw_validate (void*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ath5k_hw_set_tx_queueprops(struct ath5k_hw *ah, int queue,
				const struct ath5k_txq_info *qinfo)
{
	struct ath5k_txq_info *qi;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	qi = &ah->ah_txq[queue];

	if (qi->tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return -EIO;

	/* copy and validate values */
	qi->tqi_type = qinfo->tqi_type;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_flags = qinfo->tqi_flags;
	/*
	 * According to the docs: Although the AIFS field is 8 bit wide,
	 * the maximum supported value is 0xFC. Setting it higher than that
	 * will cause the DCU to hang.
	 */
	qi->tqi_aifs = min(qinfo->tqi_aifs, (u8)0xFC);
	qi->tqi_cw_min = ath5k_cw_validate(qinfo->tqi_cw_min);
	qi->tqi_cw_max = ath5k_cw_validate(qinfo->tqi_cw_max);
	qi->tqi_cbr_period = qinfo->tqi_cbr_period;
	qi->tqi_cbr_overflow_limit = qinfo->tqi_cbr_overflow_limit;
	qi->tqi_burst_time = qinfo->tqi_burst_time;
	qi->tqi_ready_time = qinfo->tqi_ready_time;

	/*XXX: Is this supported on 5210 ?*/
	/*XXX: Is this correct for AR5K_WME_AC_VI,VO ???*/
	if ((qinfo->tqi_type == AR5K_TX_QUEUE_DATA &&
		((qinfo->tqi_subtype == AR5K_WME_AC_VI) ||
		 (qinfo->tqi_subtype == AR5K_WME_AC_VO))) ||
	     qinfo->tqi_type == AR5K_TX_QUEUE_UAPSD)
		qi->tqi_flags |= AR5K_TXQ_FLAG_POST_FR_BKOFF_DIS;

	return 0;
}