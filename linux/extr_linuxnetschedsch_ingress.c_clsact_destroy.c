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
struct clsact_sched_data {int /*<<< orphan*/  ingress_block_info; int /*<<< orphan*/  ingress_block; int /*<<< orphan*/  egress_block_info; int /*<<< orphan*/  egress_block; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_dec_egress_queue () ; 
 int /*<<< orphan*/  net_dec_ingress_queue () ; 
 struct clsact_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_block_put_ext (int /*<<< orphan*/ ,struct Qdisc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clsact_destroy(struct Qdisc *sch)
{
	struct clsact_sched_data *q = qdisc_priv(sch);

	tcf_block_put_ext(q->egress_block, sch, &q->egress_block_info);
	tcf_block_put_ext(q->ingress_block, sch, &q->ingress_block_info);

	net_dec_ingress_queue();
	net_dec_egress_queue();
}