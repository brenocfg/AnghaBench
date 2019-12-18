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
struct thread {scalar_t__ pid_; scalar_t__ mg; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int map_groups__clone (struct thread*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int thread__prepare_access (struct thread*) ; 

__attribute__((used)) static int thread__clone_map_groups(struct thread *thread,
				    struct thread *parent,
				    bool do_maps_clone)
{
	/* This is new thread, we share map groups for process. */
	if (thread->pid_ == parent->pid_)
		return thread__prepare_access(thread);

	if (thread->mg == parent->mg) {
		pr_debug("broken map groups on thread %d/%d parent %d/%d\n",
			 thread->pid_, thread->tid, parent->pid_, parent->tid);
		return 0;
	}
	/* But this one is new process, copy maps. */
	return do_maps_clone ? map_groups__clone(thread, parent->mg) : 0;
}