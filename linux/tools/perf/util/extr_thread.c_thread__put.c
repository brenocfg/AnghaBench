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
struct thread {int /*<<< orphan*/  node; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread__delete (struct thread*) ; 

void thread__put(struct thread *thread)
{
	if (thread && refcount_dec_and_test(&thread->refcnt)) {
		/*
		 * Remove it from the dead threads list, as last reference is
		 * gone, if it is in a dead threads list.
		 *
		 * We may not be there anymore if say, the machine where it was
		 * stored was already deleted, so we already removed it from
		 * the dead threads and some other piece of code still keeps a
		 * reference.
		 *
		 * This is what 'perf sched' does and finally drops it in
		 * perf_sched__lat(), where it calls perf_sched__read_events(),
		 * that processes the events by creating a session and deleting
		 * it, which ends up destroying the list heads for the dead
		 * threads, but before it does that it removes all threads from
		 * it using list_del_init().
		 *
		 * So we need to check here if it is in a dead threads list and
		 * if so, remove it before finally deleting the thread, to avoid
		 * an use after free situation.
		 */
		if (!list_empty(&thread->node))
			list_del_init(&thread->node);
		thread__delete(thread);
	}
}