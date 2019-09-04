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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct rsi_common {int pkt_cnt; size_t selected_qnum; scalar_t__ min_weight; int /*<<< orphan*/ * tx_queue; TYPE_1__* tx_qinfo; scalar_t__ hw_data_qs_blocked; int /*<<< orphan*/  mgmt_q_block; } ;
struct TYPE_2__ {scalar_t__ weight; scalar_t__ pkt_contended; } ;

/* Variables and functions */
 size_t INVALID_QUEUE ; 
 size_t MGMT_BEACON_Q ; 
 size_t MGMT_SOFT_Q ; 
 size_t NUM_EDCA_QUEUES ; 
 size_t VI_Q ; 
 size_t VO_Q ; 
 size_t rsi_determine_min_weight_queue (struct rsi_common*) ; 
 int rsi_get_num_pkts_dequeue (struct rsi_common*,size_t) ; 
 int rsi_recalculate_weights (struct rsi_common*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 rsi_core_determine_hal_queue(struct rsi_common *common)
{
	bool recontend_queue = false;
	u32 q_len = 0;
	u8 q_num = INVALID_QUEUE;
	u8 ii = 0;

	if (skb_queue_len(&common->tx_queue[MGMT_BEACON_Q])) {
		q_num = MGMT_BEACON_Q;
		return q_num;
	}
	if (skb_queue_len(&common->tx_queue[MGMT_SOFT_Q])) {
		if (!common->mgmt_q_block)
			q_num = MGMT_SOFT_Q;
		return q_num;
	}

	if (common->hw_data_qs_blocked)
		return q_num;

	if (common->pkt_cnt != 0) {
		--common->pkt_cnt;
		return common->selected_qnum;
	}

get_queue_num:
	recontend_queue = false;

	q_num = rsi_determine_min_weight_queue(common);

	ii = q_num;

	/* Selecting the queue with least back off */
	for (; ii < NUM_EDCA_QUEUES; ii++) {
		q_len = skb_queue_len(&common->tx_queue[ii]);
		if (((common->tx_qinfo[ii].pkt_contended) &&
		     (common->tx_qinfo[ii].weight < common->min_weight)) &&
		      q_len) {
			common->min_weight = common->tx_qinfo[ii].weight;
			q_num = ii;
		}
	}

	if (q_num < NUM_EDCA_QUEUES)
		common->tx_qinfo[q_num].pkt_contended = 0;

	/* Adjust the back off values for all queues again */
	recontend_queue = rsi_recalculate_weights(common);

	q_len = skb_queue_len(&common->tx_queue[q_num]);
	if (!q_len) {
		/* If any queues are freshly contended and the selected queue
		 * doesn't have any packets
		 * then get the queue number again with fresh values
		 */
		if (recontend_queue)
			goto get_queue_num;

		q_num = INVALID_QUEUE;
		return q_num;
	}

	common->selected_qnum = q_num;
	q_len = skb_queue_len(&common->tx_queue[q_num]);

	if (q_num == VO_Q || q_num == VI_Q) {
		common->pkt_cnt = rsi_get_num_pkts_dequeue(common, q_num);
		common->pkt_cnt -= 1;
	}

	return q_num;
}