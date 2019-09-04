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
struct dl_rq {int dummy; } ;
struct rq {struct dl_rq dl; } ;

/* Variables and functions */
 struct task_struct* dl_task_of (struct sched_dl_entity*) ; 
 struct rq* task_rq (struct task_struct*) ; 

__attribute__((used)) static inline struct dl_rq *dl_rq_of_se(struct sched_dl_entity *dl_se)
{
	struct task_struct *p = dl_task_of(dl_se);
	struct rq *rq = task_rq(p);

	return &rq->dl;
}