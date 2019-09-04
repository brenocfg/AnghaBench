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
struct llc_shdlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  rcv_q; int /*<<< orphan*/  hard_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  EREMOTEIO ; 
 int /*<<< orphan*/  SHDLC_DUMP_SKB (char*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void llc_shdlc_recv_frame(struct llc_shdlc *shdlc, struct sk_buff *skb)
{
	if (skb == NULL) {
		pr_err("NULL Frame -> link is dead\n");
		shdlc->hard_fault = -EREMOTEIO;
	} else {
		SHDLC_DUMP_SKB("incoming frame", skb);
		skb_queue_tail(&shdlc->rcv_q, skb);
	}

	schedule_work(&shdlc->sm_work);
}