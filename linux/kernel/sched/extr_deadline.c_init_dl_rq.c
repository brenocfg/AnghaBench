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
struct TYPE_2__ {scalar_t__ next; scalar_t__ curr; } ;
struct dl_rq {scalar_t__ this_bw; scalar_t__ running_bw; int /*<<< orphan*/  dl_bw; void* pushable_dl_tasks_root; scalar_t__ overloaded; scalar_t__ dl_nr_migratory; TYPE_1__ earliest_dl; void* root; } ;

/* Variables and functions */
 void* RB_ROOT_CACHED ; 
 int /*<<< orphan*/  init_dl_bw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dl_rq_bw_ratio (struct dl_rq*) ; 

void init_dl_rq(struct dl_rq *dl_rq)
{
	dl_rq->root = RB_ROOT_CACHED;

#ifdef CONFIG_SMP
	/* zero means no -deadline tasks */
	dl_rq->earliest_dl.curr = dl_rq->earliest_dl.next = 0;

	dl_rq->dl_nr_migratory = 0;
	dl_rq->overloaded = 0;
	dl_rq->pushable_dl_tasks_root = RB_ROOT_CACHED;
#else
	init_dl_bw(&dl_rq->dl_bw);
#endif

	dl_rq->running_bw = 0;
	dl_rq->this_bw = 0;
	init_dl_rq_bw_ratio(dl_rq);
}