#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sched_dl_entity {int /*<<< orphan*/  deadline; } ;
struct dl_rq {int /*<<< orphan*/  dl_nr_running; } ;
struct TYPE_2__ {int prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dec_dl_deadline (struct dl_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_dl_migration (struct sched_dl_entity*,struct dl_rq*) ; 
 int /*<<< orphan*/  dl_prio (int) ; 
 TYPE_1__* dl_task_of (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  rq_of_dl_rq (struct dl_rq*) ; 
 int /*<<< orphan*/  sub_nr_running (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline
void dec_dl_tasks(struct sched_dl_entity *dl_se, struct dl_rq *dl_rq)
{
	int prio = dl_task_of(dl_se)->prio;

	WARN_ON(!dl_prio(prio));
	WARN_ON(!dl_rq->dl_nr_running);
	dl_rq->dl_nr_running--;
	sub_nr_running(rq_of_dl_rq(dl_rq), 1);

	dec_dl_deadline(dl_rq, dl_se->deadline);
	dec_dl_migration(dl_se, dl_rq);
}