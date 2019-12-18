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
struct fq_codel_sched_data {int /*<<< orphan*/  flows; int /*<<< orphan*/  backlogs; int /*<<< orphan*/  block; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 struct fq_codel_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fq_codel_destroy(struct Qdisc *sch)
{
	struct fq_codel_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	kvfree(q->backlogs);
	kvfree(q->flows);
}