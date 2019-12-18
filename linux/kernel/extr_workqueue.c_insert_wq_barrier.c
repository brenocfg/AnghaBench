#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct list_head* next; } ;
struct work_struct {TYPE_2__ entry; int /*<<< orphan*/  lockdep_map; } ;
struct wq_barrier {struct work_struct work; int /*<<< orphan*/  task; int /*<<< orphan*/  done; } ;
struct TYPE_3__ {struct list_head* next; } ;
struct worker {TYPE_1__ scheduled; } ;
struct pool_workqueue {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK_ONSTACK (struct work_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORK_NO_COLOR ; 
 unsigned long WORK_STRUCT_LINKED ; 
 int /*<<< orphan*/  WORK_STRUCT_LINKED_BIT ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING_BIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  debug_work_activate (struct work_struct*) ; 
 int /*<<< orphan*/  init_completion_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_work (struct pool_workqueue*,struct work_struct*,struct list_head*,unsigned int) ; 
 unsigned int work_color_to_flags (int /*<<< orphan*/ ) ; 
 unsigned long* work_data_bits (struct work_struct*) ; 
 int /*<<< orphan*/  wq_barrier_func ; 

__attribute__((used)) static void insert_wq_barrier(struct pool_workqueue *pwq,
			      struct wq_barrier *barr,
			      struct work_struct *target, struct worker *worker)
{
	struct list_head *head;
	unsigned int linked = 0;

	/*
	 * debugobject calls are safe here even with pool->lock locked
	 * as we know for sure that this will not trigger any of the
	 * checks and call back into the fixup functions where we
	 * might deadlock.
	 */
	INIT_WORK_ONSTACK(&barr->work, wq_barrier_func);
	__set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(&barr->work));

	init_completion_map(&barr->done, &target->lockdep_map);

	barr->task = current;

	/*
	 * If @target is currently being executed, schedule the
	 * barrier to the worker; otherwise, put it after @target.
	 */
	if (worker)
		head = worker->scheduled.next;
	else {
		unsigned long *bits = work_data_bits(target);

		head = target->entry.next;
		/* there can already be other linked works, inherit and set */
		linked = *bits & WORK_STRUCT_LINKED;
		__set_bit(WORK_STRUCT_LINKED_BIT, bits);
	}

	debug_work_activate(&barr->work);
	insert_work(pwq, &barr->work, head,
		    work_color_to_flags(WORK_NO_COLOR) | linked);
}