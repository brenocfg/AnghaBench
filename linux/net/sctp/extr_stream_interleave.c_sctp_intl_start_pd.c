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
struct sctp_ulpq {int /*<<< orphan*/  reasm_uo; int /*<<< orphan*/  reasm; } ;
struct sctp_ulpevent {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_enqueue_event (struct sctp_ulpq*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_intl_retrieve_first (struct sctp_ulpq*) ; 
 struct sctp_ulpevent* sctp_intl_retrieve_first_uo (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

__attribute__((used)) static void sctp_intl_start_pd(struct sctp_ulpq *ulpq, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sk_buff_head temp;

	if (!skb_queue_empty(&ulpq->reasm)) {
		do {
			event = sctp_intl_retrieve_first(ulpq);
			if (event) {
				skb_queue_head_init(&temp);
				__skb_queue_tail(&temp, sctp_event2skb(event));
				sctp_enqueue_event(ulpq, &temp);
			}
		} while (event);
	}

	if (!skb_queue_empty(&ulpq->reasm_uo)) {
		do {
			event = sctp_intl_retrieve_first_uo(ulpq);
			if (event) {
				skb_queue_head_init(&temp);
				__skb_queue_tail(&temp, sctp_event2skb(event));
				sctp_enqueue_event(ulpq, &temp);
			}
		} while (event);
	}
}