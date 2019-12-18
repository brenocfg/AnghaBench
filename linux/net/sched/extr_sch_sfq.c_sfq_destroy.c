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
struct sfq_sched_data {int /*<<< orphan*/  red_parms; int /*<<< orphan*/  slots; int /*<<< orphan*/  ht; int /*<<< orphan*/  perturb_timer; scalar_t__ perturb_period; int /*<<< orphan*/  block; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sfq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfq_destroy(struct Qdisc *sch)
{
	struct sfq_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	q->perturb_period = 0;
	del_timer_sync(&q->perturb_timer);
	sfq_free(q->ht);
	sfq_free(q->slots);
	kfree(q->red_parms);
}