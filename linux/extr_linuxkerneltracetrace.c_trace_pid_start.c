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
struct trace_pid_list {unsigned long pid_max; int /*<<< orphan*/  pids; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 unsigned long find_first_bit (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ trace_pid_next (struct trace_pid_list*,void*,scalar_t__*) ; 

void *trace_pid_start(struct trace_pid_list *pid_list, loff_t *pos)
{
	unsigned long pid;
	loff_t l = 0;

	pid = find_first_bit(pid_list->pids, pid_list->pid_max);
	if (pid >= pid_list->pid_max)
		return NULL;

	/* Return pid + 1 so that zero can be the exit value */
	for (pid++; pid && l < *pos;
	     pid = (unsigned long)trace_pid_next(pid_list, (void *)pid, &l))
		;
	return (void *)pid;
}