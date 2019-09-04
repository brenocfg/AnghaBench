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
struct wait_opts {int wo_flags; } ;
struct task_struct {scalar_t__ exit_signal; } ;

/* Variables and functions */
 scalar_t__ SIGCHLD ; 
 int __WALL ; 
 int __WCLONE ; 
 int /*<<< orphan*/  eligible_pid (struct wait_opts*,struct task_struct*) ; 

__attribute__((used)) static int
eligible_child(struct wait_opts *wo, bool ptrace, struct task_struct *p)
{
	if (!eligible_pid(wo, p))
		return 0;

	/*
	 * Wait for all children (clone and not) if __WALL is set or
	 * if it is traced by us.
	 */
	if (ptrace || (wo->wo_flags & __WALL))
		return 1;

	/*
	 * Otherwise, wait for clone children *only* if __WCLONE is set;
	 * otherwise, wait for non-clone children *only*.
	 *
	 * Note: a "clone" child here is one that reports to its parent
	 * using a signal other than SIGCHLD, or a non-leader thread which
	 * we can only see if it is traced by us.
	 */
	if ((p->exit_signal != SIGCHLD) ^ !!(wo->wo_flags & __WCLONE))
		return 0;

	return 1;
}