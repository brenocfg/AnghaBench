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
struct thread {int pid_; int tid; scalar_t__ mg; } ;
struct machine {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 struct thread* __machine__findnew_thread (struct machine*,int,int) ; 
 int /*<<< orphan*/  map_groups__empty (scalar_t__) ; 
 scalar_t__ map_groups__get (scalar_t__) ; 
 scalar_t__ map_groups__new (struct machine*) ; 
 int /*<<< orphan*/  map_groups__put (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

__attribute__((used)) static void machine__update_thread_pid(struct machine *machine,
				       struct thread *th, pid_t pid)
{
	struct thread *leader;

	if (pid == th->pid_ || pid == -1 || th->pid_ != -1)
		return;

	th->pid_ = pid;

	if (th->pid_ == th->tid)
		return;

	leader = __machine__findnew_thread(machine, th->pid_, th->pid_);
	if (!leader)
		goto out_err;

	if (!leader->mg)
		leader->mg = map_groups__new(machine);

	if (!leader->mg)
		goto out_err;

	if (th->mg == leader->mg)
		return;

	if (th->mg) {
		/*
		 * Maps are created from MMAP events which provide the pid and
		 * tid.  Consequently there never should be any maps on a thread
		 * with an unknown pid.  Just print an error if there are.
		 */
		if (!map_groups__empty(th->mg))
			pr_err("Discarding thread maps for %d:%d\n",
			       th->pid_, th->tid);
		map_groups__put(th->mg);
	}

	th->mg = map_groups__get(leader->mg);
out_put:
	thread__put(leader);
	return;
out_err:
	pr_err("Failed to join map groups for %d:%d\n", th->pid_, th->tid);
	goto out_put;
}