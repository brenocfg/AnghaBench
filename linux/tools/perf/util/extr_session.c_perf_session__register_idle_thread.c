#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_1__ machines; } ;

/* Variables and functions */
 struct thread* machine__findnew_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 
 scalar_t__ thread__set_comm (struct thread*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread__set_namespaces (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int perf_session__register_idle_thread(struct perf_session *session)
{
	struct thread *thread;
	int err = 0;

	thread = machine__findnew_thread(&session->machines.host, 0, 0);
	if (thread == NULL || thread__set_comm(thread, "swapper", 0)) {
		pr_err("problem inserting idle task.\n");
		err = -1;
	}

	if (thread == NULL || thread__set_namespaces(thread, 0, NULL)) {
		pr_err("problem inserting idle task.\n");
		err = -1;
	}

	/* machine__findnew_thread() got the thread, so put it */
	thread__put(thread);
	return err;
}