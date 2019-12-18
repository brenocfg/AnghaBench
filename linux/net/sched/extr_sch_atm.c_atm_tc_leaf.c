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
struct atm_flow_data {struct Qdisc* q; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct atm_flow_data*) ; 

__attribute__((used)) static struct Qdisc *atm_tc_leaf(struct Qdisc *sch, unsigned long cl)
{
	struct atm_flow_data *flow = (struct atm_flow_data *)cl;

	pr_debug("atm_tc_leaf(sch %p,flow %p)\n", sch, flow);
	return flow ? flow->q : NULL;
}