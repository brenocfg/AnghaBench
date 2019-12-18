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
struct task_struct {size_t pid; int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 size_t PID_MAX_DEFAULT ; 
 int /*<<< orphan*/ * tgid_map ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int trace_save_tgid(struct task_struct *tsk)
{
	/* treat recording of idle task as a success */
	if (!tsk->pid)
		return 1;

	if (unlikely(!tgid_map || tsk->pid > PID_MAX_DEFAULT))
		return 0;

	tgid_map[tsk->pid] = tsk->tgid;
	return 1;
}