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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 unsigned long find_next_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

void *trace_pid_next(struct trace_pid_list *pid_list, void *v, loff_t *pos)
{
	unsigned long pid = (unsigned long)v;

	(*pos)++;

	/* pid already is +1 of the actual prevous bit */
	pid = find_next_bit(pid_list->pids, pid_list->pid_max, pid);

	/* Return pid + 1 to allow zero to be represented */
	if (pid < pid_list->pid_max)
		return (void *)(pid + 1);

	return NULL;
}