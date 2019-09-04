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
struct thread {int pid_; int tid; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ procfs__read_str (char*,char**,size_t*) ; 
 int snprintf (char*,int,char*,int,int) ; 
 int thread__set_comm (struct thread*,char*,int /*<<< orphan*/ ) ; 

int thread__set_comm_from_proc(struct thread *thread)
{
	char path[64];
	char *comm = NULL;
	size_t sz;
	int err = -1;

	if (!(snprintf(path, sizeof(path), "%d/task/%d/comm",
		       thread->pid_, thread->tid) >= (int)sizeof(path)) &&
	    procfs__read_str(path, &comm, &sz) == 0) {
		comm[sz - 1] = '\0';
		err = thread__set_comm(thread, comm, 0);
	}

	return err;
}