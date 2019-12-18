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
struct task_struct {int dummy; } ;
struct sched_dl_entity {int dummy; } ;
struct rq_flags {int dummy; } ;
struct dl_rq {int dummy; } ;
struct rq {struct dl_rq dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct task_struct* dl_task_of (struct sched_dl_entity*) ; 
 struct sched_dl_entity* pick_next_dl_entity (struct rq*,struct dl_rq*) ; 
 int /*<<< orphan*/  sched_dl_runnable (struct rq*) ; 
 int /*<<< orphan*/  set_next_task_dl (struct rq*,struct task_struct*) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_dl(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct sched_dl_entity *dl_se;
	struct dl_rq *dl_rq = &rq->dl;
	struct task_struct *p;

	WARN_ON_ONCE(prev || rf);

	if (!sched_dl_runnable(rq))
		return NULL;

	dl_se = pick_next_dl_entity(rq, dl_rq);
	BUG_ON(!dl_se);
	p = dl_task_of(dl_se);
	set_next_task_dl(rq, p);
	return p;
}