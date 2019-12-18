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
struct cbq_class {scalar_t__ defmap; int /*<<< orphan*/  tparent; scalar_t__ next_alive; int /*<<< orphan*/  q; scalar_t__ children; scalar_t__ filters; } ;
struct cbq_sched_data {struct cbq_class* rx_class; struct cbq_class* tx_borrowed; struct cbq_class* tx_class; struct cbq_class link; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cbq_adjust_levels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbq_deactivate_class (struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_destroy_class (struct Qdisc*,struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_rmprio (struct cbq_sched_data*,struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_sync_defmap (struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_unlink_class (struct cbq_class*) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_purge_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int cbq_delete(struct Qdisc *sch, unsigned long arg)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct cbq_class *cl = (struct cbq_class *)arg;

	if (cl->filters || cl->children || cl == &q->link)
		return -EBUSY;

	sch_tree_lock(sch);

	qdisc_purge_queue(cl->q);

	if (cl->next_alive)
		cbq_deactivate_class(cl);

	if (q->tx_borrowed == cl)
		q->tx_borrowed = q->tx_class;
	if (q->tx_class == cl) {
		q->tx_class = NULL;
		q->tx_borrowed = NULL;
	}
#ifdef CONFIG_NET_CLS_ACT
	if (q->rx_class == cl)
		q->rx_class = NULL;
#endif

	cbq_unlink_class(cl);
	cbq_adjust_levels(cl->tparent);
	cl->defmap = 0;
	cbq_sync_defmap(cl);

	cbq_rmprio(q, cl);
	sch_tree_unlock(sch);

	cbq_destroy_class(sch, cl);
	return 0;
}