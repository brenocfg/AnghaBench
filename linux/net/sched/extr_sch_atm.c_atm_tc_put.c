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
struct atm_flow_data {scalar_t__ excess; TYPE_2__* sock; int /*<<< orphan*/  old_pop; TYPE_1__* vcc; int /*<<< orphan*/  block; int /*<<< orphan*/  q; int /*<<< orphan*/  list; scalar_t__ ref; } ;
struct atm_qdisc_data {struct atm_flow_data link; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  pop; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atm_flow_data*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfd_put (TYPE_2__*) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atm_tc_put(struct Qdisc *sch, unsigned long cl)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);
	struct atm_flow_data *flow = (struct atm_flow_data *)cl;

	pr_debug("atm_tc_put(sch %p,[qdisc %p],flow %p)\n", sch, p, flow);
	if (--flow->ref)
		return;
	pr_debug("atm_tc_put: destroying\n");
	list_del_init(&flow->list);
	pr_debug("atm_tc_put: qdisc %p\n", flow->q);
	qdisc_put(flow->q);
	tcf_block_put(flow->block);
	if (flow->sock) {
		pr_debug("atm_tc_put: f_count %ld\n",
			file_count(flow->sock->file));
		flow->vcc->pop = flow->old_pop;
		sockfd_put(flow->sock);
	}
	if (flow->excess)
		atm_tc_put(sch, (unsigned long)flow->excess);
	if (flow != &p->link)
		kfree(flow);
	/*
	 * If flow == &p->link, the qdisc no longer works at this point and
	 * needs to be removed. (By the caller of atm_tc_put.)
	 */
}