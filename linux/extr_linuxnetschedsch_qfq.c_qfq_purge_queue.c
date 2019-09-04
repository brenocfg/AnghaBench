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
struct qfq_class {TYPE_3__* qdisc; } ;
struct TYPE_6__ {unsigned int backlog; } ;
struct TYPE_5__ {unsigned int qlen; } ;
struct TYPE_7__ {TYPE_2__ qstats; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (TYPE_3__*,unsigned int,unsigned int) ; 

__attribute__((used)) static void qfq_purge_queue(struct qfq_class *cl)
{
	unsigned int len = cl->qdisc->q.qlen;
	unsigned int backlog = cl->qdisc->qstats.backlog;

	qdisc_reset(cl->qdisc);
	qdisc_tree_reduce_backlog(cl->qdisc, len, backlog);
}