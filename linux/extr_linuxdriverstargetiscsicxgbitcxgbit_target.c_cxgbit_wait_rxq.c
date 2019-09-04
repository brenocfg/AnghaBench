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
struct sk_buff {int dummy; } ;
struct cxgbit_sock {int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ cxgbit_rx_skb (struct cxgbit_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbit_rxq_len (struct cxgbit_sock*,struct sk_buff_head*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgbit_wait_rxq(struct cxgbit_sock *csk)
{
	struct sk_buff *skb;
	struct sk_buff_head rxq;

	skb_queue_head_init(&rxq);

	wait_event_interruptible(csk->waitq, cxgbit_rxq_len(csk, &rxq));

	if (signal_pending(current))
		goto out;

	while ((skb = __skb_dequeue(&rxq))) {
		if (cxgbit_rx_skb(csk, skb))
			goto out;
	}

	return 0;
out:
	__skb_queue_purge(&rxq);
	return -1;
}