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
struct sk_buff {int dummy; } ;
struct llc_shdlc {int /*<<< orphan*/  dnr; int /*<<< orphan*/  ns; int /*<<< orphan*/  send_q; int /*<<< orphan*/  ack_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void llc_shdlc_requeue_ack_pending(struct llc_shdlc *shdlc)
{
	struct sk_buff *skb;

	pr_debug("ns reset to %d\n", shdlc->dnr);

	while ((skb = skb_dequeue_tail(&shdlc->ack_pending_q))) {
		skb_pull(skb, 1);	/* remove control field */
		skb_queue_head(&shdlc->send_q, skb);
	}
	shdlc->ns = shdlc->dnr;
}