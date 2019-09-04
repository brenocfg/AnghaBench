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
struct sk_buff {scalar_t__ cb; } ;
struct llc_shdlc {int dnr; int t2_active; int /*<<< orphan*/  t2_timer; int /*<<< orphan*/  ack_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHDLC_T2_VALUE_MS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_shdlc_reset_t2(struct llc_shdlc *shdlc, int y_nr)
{
	struct sk_buff *skb;
	int dnr = shdlc->dnr;	/* MUST initially be < y_nr */

	pr_debug("release ack pending up to frame %d excluded\n", y_nr);

	while (dnr != y_nr) {
		pr_debug("release ack pending frame %d\n", dnr);

		skb = skb_dequeue(&shdlc->ack_pending_q);
		kfree_skb(skb);

		dnr = (dnr + 1) % 8;
	}

	if (skb_queue_empty(&shdlc->ack_pending_q)) {
		if (shdlc->t2_active) {
			del_timer_sync(&shdlc->t2_timer);
			shdlc->t2_active = false;

			pr_debug
			    ("All sent frames acked. Stopped T2(retransmit)\n");
		}
	} else {
		skb = skb_peek(&shdlc->ack_pending_q);

		mod_timer(&shdlc->t2_timer, *(unsigned long *)skb->cb +
			  msecs_to_jiffies(SHDLC_T2_VALUE_MS));
		shdlc->t2_active = true;

		pr_debug
		    ("Start T2(retransmit) for remaining unacked sent frames\n");
	}
}