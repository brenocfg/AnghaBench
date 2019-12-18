#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  tstamp; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * last_run_head; int /*<<< orphan*/ * fragments_tail; int /*<<< orphan*/  rb_fragments; int /*<<< orphan*/  stamp; } ;
struct lowpan_frag_queue {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  inet_frag_kill (TYPE_1__*) ; 
 int /*<<< orphan*/  inet_frag_reasm_finish (TYPE_1__*,struct sk_buff*,void*,int) ; 
 void* inet_frag_reasm_prepare (TYPE_1__*,struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 

__attribute__((used)) static int lowpan_frag_reasm(struct lowpan_frag_queue *fq, struct sk_buff *skb,
			     struct sk_buff *prev_tail, struct net_device *ldev)
{
	void *reasm_data;

	inet_frag_kill(&fq->q);

	reasm_data = inet_frag_reasm_prepare(&fq->q, skb, prev_tail);
	if (!reasm_data)
		goto out_oom;
	inet_frag_reasm_finish(&fq->q, skb, reasm_data, false);

	skb->dev = ldev;
	skb->tstamp = fq->q.stamp;
	fq->q.rb_fragments = RB_ROOT;
	fq->q.fragments_tail = NULL;
	fq->q.last_run_head = NULL;

	return 1;
out_oom:
	net_dbg_ratelimited("lowpan_frag_reasm: no memory for reassembly\n");
	return -1;
}