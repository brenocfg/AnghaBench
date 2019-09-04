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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct efx_ptp_match {scalar_t__ state; int /*<<< orphan*/  expiry; } ;
struct efx_ptp_data {int /*<<< orphan*/  rxq; int /*<<< orphan*/  rx_no_timestamp; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;

/* Variables and functions */
 scalar_t__ PTP_PACKET_STATE_MATCHED ; 
 scalar_t__ PTP_PACKET_STATE_MATCH_UNWANTED ; 
 scalar_t__ PTP_PACKET_STATE_TIMED_OUT ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ efx_ptp_match_rx (struct efx_nic*,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ptp_process_events(struct efx_nic *efx, struct sk_buff_head *q)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&ptp->rxq))) {
		struct efx_ptp_match *match;

		match = (struct efx_ptp_match *)skb->cb;
		if (match->state == PTP_PACKET_STATE_MATCH_UNWANTED) {
			__skb_queue_tail(q, skb);
		} else if (efx_ptp_match_rx(efx, skb) ==
			   PTP_PACKET_STATE_MATCHED) {
			__skb_queue_tail(q, skb);
		} else if (time_after(jiffies, match->expiry)) {
			match->state = PTP_PACKET_STATE_TIMED_OUT;
			++ptp->rx_no_timestamp;
			__skb_queue_tail(q, skb);
		} else {
			/* Replace unprocessed entry and stop */
			skb_queue_head(&ptp->rxq, skb);
			break;
		}
	}
}