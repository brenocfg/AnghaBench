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
struct llt_ndlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  rcv_q; int /*<<< orphan*/  hard_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  EREMOTEIO ; 
 int /*<<< orphan*/  NDLC_DUMP_SKB (char*,struct sk_buff*) ; 
 int /*<<< orphan*/  ndlc_close (struct llt_ndlc*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void ndlc_recv(struct llt_ndlc *ndlc, struct sk_buff *skb)
{
	if (skb == NULL) {
		pr_err("NULL Frame -> link is dead\n");
		ndlc->hard_fault = -EREMOTEIO;
		ndlc_close(ndlc);
	} else {
		NDLC_DUMP_SKB("incoming frame", skb);
		skb_queue_tail(&ndlc->rcv_q, skb);
	}

	schedule_work(&ndlc->sm_work);
}