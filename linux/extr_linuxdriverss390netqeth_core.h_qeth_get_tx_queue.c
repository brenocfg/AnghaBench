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
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_2__ {int no_out_queues; size_t default_out_queue; struct qeth_qdio_out_q** out_qs; int /*<<< orphan*/  do_prio_queueing; } ;
struct qeth_card {TYPE_1__ qdio; } ;

/* Variables and functions */
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int RTN_UNICAST ; 
 size_t qeth_get_priority_queue (struct qeth_card*,struct sk_buff*,int) ; 

__attribute__((used)) static inline struct qeth_qdio_out_q *qeth_get_tx_queue(struct qeth_card *card,
							struct sk_buff *skb,
							int ipv, int cast_type)
{
	if (IS_IQD(card) && cast_type != RTN_UNICAST)
		return card->qdio.out_qs[card->qdio.no_out_queues - 1];
	if (!card->qdio.do_prio_queueing)
		return card->qdio.out_qs[card->qdio.default_out_queue];
	return card->qdio.out_qs[qeth_get_priority_queue(card, skb, ipv)];
}