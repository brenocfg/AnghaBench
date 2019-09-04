#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qfq_class {scalar_t__ deficit; int /*<<< orphan*/  alist; TYPE_3__* qdisc; } ;
struct qfq_aggregate {scalar_t__ lmax; int /*<<< orphan*/  active; } ;
struct TYPE_6__ {scalar_t__ qlen; } ;
struct TYPE_7__ {TYPE_1__* ops; TYPE_2__ q; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* peek ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_dequeue_peeked (TYPE_3__*) ; 
 scalar_t__ qdisc_pkt_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void agg_dequeue(struct qfq_aggregate *agg,
			struct qfq_class *cl, unsigned int len)
{
	qdisc_dequeue_peeked(cl->qdisc);

	cl->deficit -= (int) len;

	if (cl->qdisc->q.qlen == 0) /* no more packets, remove from list */
		list_del(&cl->alist);
	else if (cl->deficit < qdisc_pkt_len(cl->qdisc->ops->peek(cl->qdisc))) {
		cl->deficit += agg->lmax;
		list_move_tail(&cl->alist, &agg->active);
	}
}