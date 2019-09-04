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
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread__delete (struct thread*) ; 

void thread__put(struct thread *thread)
{
	if (thread && refcount_dec_and_test(&thread->refcnt)) {
		/*
		 * Remove it from the dead_threads list, as last reference
		 * is gone.
		 */
		list_del_init(&thread->node);
		thread__delete(thread);
	}
}