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
struct atm_flow_data {int ref; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  list; } ;
struct atm_qdisc_data {struct atm_flow_data link; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  atm_tc_put (struct Qdisc*,unsigned long) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct atm_qdisc_data*,struct atm_flow_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atm_tc_delete(struct Qdisc *sch, unsigned long arg)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);
	struct atm_flow_data *flow = (struct atm_flow_data *)arg;

	pr_debug("atm_tc_delete(sch %p,[qdisc %p],flow %p)\n", sch, p, flow);
	if (list_empty(&flow->list))
		return -EINVAL;
	if (rcu_access_pointer(flow->filter_list) || flow == &p->link)
		return -EBUSY;
	/*
	 * Reference count must be 2: one for "keepalive" (set at class
	 * creation), and one for the reference held when calling delete.
	 */
	if (flow->ref < 2) {
		pr_err("atm_tc_delete: flow->ref == %d\n", flow->ref);
		return -EINVAL;
	}
	if (flow->ref > 2)
		return -EBUSY;	/* catch references via excess, etc. */
	atm_tc_put(sch, arg);
	return 0;
}