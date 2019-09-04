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
struct ath5k_txq_info {unsigned int tqi_subtype; int tqi_type; } ;
struct TYPE_4__ {int q_tx_num; } ;
struct TYPE_5__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_txq_status; TYPE_3__* ah_txq; TYPE_2__ ah_capabilities; } ;
typedef  enum ath5k_tx_queue { ____Placeholder_ath5k_tx_queue } ath5k_tx_queue ;
struct TYPE_6__ {int tqi_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_Q_ENABLE_BITS (int /*<<< orphan*/ ,unsigned int) ; 
#define  AR5K_TX_QUEUE_BEACON 131 
#define  AR5K_TX_QUEUE_CAB 130 
#define  AR5K_TX_QUEUE_DATA 129 
 unsigned int AR5K_TX_QUEUE_ID_BEACON ; 
 unsigned int AR5K_TX_QUEUE_ID_CAB ; 
 unsigned int AR5K_TX_QUEUE_ID_NOQCU_BEACON ; 
 unsigned int AR5K_TX_QUEUE_ID_NOQCU_DATA ; 
 unsigned int AR5K_TX_QUEUE_ID_UAPSD ; 
#define  AR5K_TX_QUEUE_UAPSD 128 
 int EINVAL ; 
 int ath5k_hw_set_tx_queueprops (struct ath5k_hw*,unsigned int,struct ath5k_txq_info*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int
ath5k_hw_setup_tx_queue(struct ath5k_hw *ah, enum ath5k_tx_queue queue_type,
		struct ath5k_txq_info *queue_info)
{
	unsigned int queue;
	int ret;

	/*
	 * Get queue by type
	 */
	/* 5210 only has 2 queues */
	if (ah->ah_capabilities.cap_queues.q_tx_num == 2) {
		switch (queue_type) {
		case AR5K_TX_QUEUE_DATA:
			queue = AR5K_TX_QUEUE_ID_NOQCU_DATA;
			break;
		case AR5K_TX_QUEUE_BEACON:
		case AR5K_TX_QUEUE_CAB:
			queue = AR5K_TX_QUEUE_ID_NOQCU_BEACON;
			break;
		default:
			return -EINVAL;
		}
	} else {
		switch (queue_type) {
		case AR5K_TX_QUEUE_DATA:
			queue = queue_info->tqi_subtype;
			break;
		case AR5K_TX_QUEUE_UAPSD:
			queue = AR5K_TX_QUEUE_ID_UAPSD;
			break;
		case AR5K_TX_QUEUE_BEACON:
			queue = AR5K_TX_QUEUE_ID_BEACON;
			break;
		case AR5K_TX_QUEUE_CAB:
			queue = AR5K_TX_QUEUE_ID_CAB;
			break;
		default:
			return -EINVAL;
		}
	}

	/*
	 * Setup internal queue structure
	 */
	memset(&ah->ah_txq[queue], 0, sizeof(struct ath5k_txq_info));
	ah->ah_txq[queue].tqi_type = queue_type;

	if (queue_info != NULL) {
		queue_info->tqi_type = queue_type;
		ret = ath5k_hw_set_tx_queueprops(ah, queue, queue_info);
		if (ret)
			return ret;
	}

	/*
	 * We use ah_txq_status to hold a temp value for
	 * the Secondary interrupt mask registers on 5211+
	 * check out ath5k_hw_reset_tx_queue
	 */
	AR5K_Q_ENABLE_BITS(ah->ah_txq_status, queue);

	return queue;
}