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
struct timer_list {int dummy; } ;
struct sfq_sched_data {scalar_t__ perturb_period; int /*<<< orphan*/  perturb_timer; scalar_t__ tail; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  perturbation; struct Qdisc* sch; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 struct sfq_sched_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  perturb_timer ; 
 int /*<<< orphan*/  prandom_u32 () ; 
 struct sfq_sched_data* q ; 
 int /*<<< orphan*/ * qdisc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_root_sleeping (struct Qdisc*) ; 
 int /*<<< orphan*/  sfq_rehash (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sfq_perturbation(struct timer_list *t)
{
	struct sfq_sched_data *q = from_timer(q, t, perturb_timer);
	struct Qdisc *sch = q->sch;
	spinlock_t *root_lock = qdisc_lock(qdisc_root_sleeping(sch));

	spin_lock(root_lock);
	q->perturbation = prandom_u32();
	if (!q->filter_list && q->tail)
		sfq_rehash(sch);
	spin_unlock(root_lock);

	if (q->perturb_period)
		mod_timer(&q->perturb_timer, jiffies + q->perturb_period);
}