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
struct sk_buff {scalar_t__ len; } ;
struct llc_shdlc {scalar_t__ state; int nr; int t1_active; int dnr; int /*<<< orphan*/  ns; int /*<<< orphan*/  hdev; int /*<<< orphan*/  (* rcv_to_hci ) (int /*<<< orphan*/ ,struct sk_buff*) ;int /*<<< orphan*/  w; int /*<<< orphan*/  t1_timer; } ;

/* Variables and functions */
 scalar_t__ SHDLC_CONNECTED ; 
 int /*<<< orphan*/  SHDLC_T1_VALUE_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FRAME_REJ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_shdlc_reset_t2 (struct llc_shdlc*,int) ; 
 int /*<<< orphan*/  llc_shdlc_send_s_frame (struct llc_shdlc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ llc_shdlc_x_lt_y_lteq_z (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void llc_shdlc_rcv_i_frame(struct llc_shdlc *shdlc,
				  struct sk_buff *skb, int ns, int nr)
{
	int x_ns = ns;
	int y_nr = nr;

	pr_debug("recvd I-frame %d, remote waiting frame %d\n", ns, nr);

	if (shdlc->state != SHDLC_CONNECTED)
		goto exit;

	if (x_ns != shdlc->nr) {
		llc_shdlc_send_s_frame(shdlc, S_FRAME_REJ, shdlc->nr);
		goto exit;
	}

	if (shdlc->t1_active == false) {
		shdlc->t1_active = true;
		mod_timer(&shdlc->t1_timer, jiffies +
			  msecs_to_jiffies(SHDLC_T1_VALUE_MS(shdlc->w)));
		pr_debug("(re)Start T1(send ack)\n");
	}

	if (skb->len) {
		shdlc->rcv_to_hci(shdlc->hdev, skb);
		skb = NULL;
	}

	shdlc->nr = (shdlc->nr + 1) % 8;

	if (llc_shdlc_x_lt_y_lteq_z(shdlc->dnr, y_nr, shdlc->ns)) {
		llc_shdlc_reset_t2(shdlc, y_nr);

		shdlc->dnr = y_nr;
	}

exit:
	kfree_skb(skb);
}