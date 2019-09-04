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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct wmm_qinfo {int pkt_contended; scalar_t__ weight; scalar_t__ wme_params; } ;
struct rsi_common {scalar_t__ min_weight; int /*<<< orphan*/ * tx_queue; struct wmm_qinfo* tx_qinfo; } ;

/* Variables and functions */
 size_t NUM_EDCA_QUEUES ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rsi_recalculate_weights(struct rsi_common *common)
{
	struct wmm_qinfo *tx_qinfo = common->tx_qinfo;
	bool recontend_queue = false;
	u8 ii = 0;
	u32 q_len = 0;

	for (ii = 0; ii < NUM_EDCA_QUEUES; ii++) {
		q_len = skb_queue_len(&common->tx_queue[ii]);
		/* Check for the need of contention */
		if (q_len) {
			if (tx_qinfo[ii].pkt_contended) {
				tx_qinfo[ii].weight =
				((tx_qinfo[ii].weight > common->min_weight) ?
				 tx_qinfo[ii].weight - common->min_weight : 0);
			} else {
				tx_qinfo[ii].pkt_contended = 1;
				tx_qinfo[ii].weight = tx_qinfo[ii].wme_params;
				recontend_queue = true;
			}
		} else { /* No packets so no contention */
			tx_qinfo[ii].weight = 0;
			tx_qinfo[ii].pkt_contended = 0;
		}
	}

	return recontend_queue;
}