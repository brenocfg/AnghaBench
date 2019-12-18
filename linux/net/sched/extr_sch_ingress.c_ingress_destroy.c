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
struct ingress_sched_data {int /*<<< orphan*/  block_info; int /*<<< orphan*/  block; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_dec_ingress_queue () ; 
 struct ingress_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_block_put_ext (int /*<<< orphan*/ ,struct Qdisc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ingress_destroy(struct Qdisc *sch)
{
	struct ingress_sched_data *q = qdisc_priv(sch);

	tcf_block_put_ext(q->block, sch, &q->block_info);
	net_dec_ingress_queue();
}