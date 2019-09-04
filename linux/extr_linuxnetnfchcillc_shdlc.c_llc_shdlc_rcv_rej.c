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
struct llc_shdlc {int dnr; int t2_active; int /*<<< orphan*/  ack_pending_q; int /*<<< orphan*/  t2_timer; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_shdlc_requeue_ack_pending (struct llc_shdlc*) ; 
 scalar_t__ llc_shdlc_x_lteq_y_lt_z (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_shdlc_rcv_rej(struct llc_shdlc *shdlc, int y_nr)
{
	struct sk_buff *skb;

	pr_debug("remote asks retransmission from frame %d\n", y_nr);

	if (llc_shdlc_x_lteq_y_lt_z(shdlc->dnr, y_nr, shdlc->ns)) {
		if (shdlc->t2_active) {
			del_timer_sync(&shdlc->t2_timer);
			shdlc->t2_active = false;
			pr_debug("Stopped T2(retransmit)\n");
		}

		if (shdlc->dnr != y_nr) {
			while ((shdlc->dnr = ((shdlc->dnr + 1) % 8)) != y_nr) {
				skb = skb_dequeue(&shdlc->ack_pending_q);
				kfree_skb(skb);
			}
		}

		llc_shdlc_requeue_ack_pending(shdlc);
	}
}