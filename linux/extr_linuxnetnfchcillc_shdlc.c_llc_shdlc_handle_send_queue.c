#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct llc_shdlc {int ns; int rnr; scalar_t__ w; int t1_active; int nr; int (* xmit_to_drv ) (int /*<<< orphan*/ ,struct sk_buff*) ;int hard_fault; int t2_active; int /*<<< orphan*/  t2_timer; TYPE_1__ ack_pending_q; int /*<<< orphan*/  hdev; TYPE_2__ send_q; int /*<<< orphan*/  t1_timer; int /*<<< orphan*/  dnr; } ;

/* Variables and functions */
 int SHDLC_CONTROL_HEAD_I ; 
 int /*<<< orphan*/  SHDLC_DUMP_SKB (char*,struct sk_buff*) ; 
 int /*<<< orphan*/  SHDLC_T2_VALUE_MS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ llc_shdlc_w_used (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct sk_buff* skb_dequeue (TYPE_2__*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void llc_shdlc_handle_send_queue(struct llc_shdlc *shdlc)
{
	struct sk_buff *skb;
	int r;
	unsigned long time_sent;

	if (shdlc->send_q.qlen)
		pr_debug
		    ("sendQlen=%d ns=%d dnr=%d rnr=%s w_room=%d unackQlen=%d\n",
		     shdlc->send_q.qlen, shdlc->ns, shdlc->dnr,
		     shdlc->rnr == false ? "false" : "true",
		     shdlc->w - llc_shdlc_w_used(shdlc->ns, shdlc->dnr),
		     shdlc->ack_pending_q.qlen);

	while (shdlc->send_q.qlen && shdlc->ack_pending_q.qlen < shdlc->w &&
	       (shdlc->rnr == false)) {

		if (shdlc->t1_active) {
			del_timer_sync(&shdlc->t1_timer);
			shdlc->t1_active = false;
			pr_debug("Stopped T1(send ack)\n");
		}

		skb = skb_dequeue(&shdlc->send_q);

		*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_I | (shdlc->ns << 3) |
					shdlc->nr;

		pr_debug("Sending I-Frame %d, waiting to rcv %d\n", shdlc->ns,
			 shdlc->nr);
		SHDLC_DUMP_SKB("shdlc frame written", skb);

		r = shdlc->xmit_to_drv(shdlc->hdev, skb);
		if (r < 0) {
			shdlc->hard_fault = r;
			break;
		}

		shdlc->ns = (shdlc->ns + 1) % 8;

		time_sent = jiffies;
		*(unsigned long *)skb->cb = time_sent;

		skb_queue_tail(&shdlc->ack_pending_q, skb);

		if (shdlc->t2_active == false) {
			shdlc->t2_active = true;
			mod_timer(&shdlc->t2_timer, time_sent +
				  msecs_to_jiffies(SHDLC_T2_VALUE_MS));
			pr_debug("Started T2 (retransmit)\n");
		}
	}
}