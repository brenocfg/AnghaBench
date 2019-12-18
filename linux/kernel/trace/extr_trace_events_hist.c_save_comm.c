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
struct task_struct {scalar_t__ pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void save_comm(char *comm, struct task_struct *task)
{
	if (!task->pid) {
		strcpy(comm, "<idle>");
		return;
	}

	if (WARN_ON_ONCE(task->pid < 0)) {
		strcpy(comm, "<XXX>");
		return;
	}

	strncpy(comm, task->comm, TASK_COMM_LEN);
}