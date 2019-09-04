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
struct red_sched_data {int /*<<< orphan*/  adapt_timer; int /*<<< orphan*/  vars; int /*<<< orphan*/  parms; struct Qdisc* sch; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  adapt_timer ; 
 struct red_sched_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct red_sched_data* q ; 
 int /*<<< orphan*/ * qdisc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_root_sleeping (struct Qdisc*) ; 
 int /*<<< orphan*/  red_adaptative_algo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void red_adaptative_timer(struct timer_list *t)
{
	struct red_sched_data *q = from_timer(q, t, adapt_timer);
	struct Qdisc *sch = q->sch;
	spinlock_t *root_lock = qdisc_lock(qdisc_root_sleeping(sch));

	spin_lock(root_lock);
	red_adaptative_algo(&q->parms, &q->vars);
	mod_timer(&q->adapt_timer, jiffies + HZ/2);
	spin_unlock(root_lock);
}