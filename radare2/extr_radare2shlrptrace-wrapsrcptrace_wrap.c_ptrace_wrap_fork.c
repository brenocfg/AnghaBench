#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void (* child_callback ) (void*) ;int* _errno; void* child_callback_user; } ;
struct TYPE_6__ {TYPE_1__ fork; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ th; scalar_t__ fork_result; int /*<<< orphan*/  result_sem; int /*<<< orphan*/  request_sem; TYPE_2__ request; } ;
typedef  TYPE_3__ ptrace_wrap_instance ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_WRAP_REQUEST_TYPE_FORK ; 
 int errno ; 
 scalar_t__ fork () ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

pid_t ptrace_wrap_fork(ptrace_wrap_instance *inst, void (*child_callback)(void *), void *child_callback_user) {
	if (inst->th == pthread_self ()) {
		pid_t r = fork ();
		if (r == 0) {
			child_callback (child_callback_user);
			return 0;
		} else {
			return r;
		}
	}

	int _errno = 0;
	inst->request.type = PTRACE_WRAP_REQUEST_TYPE_FORK;
	inst->request.fork.child_callback = child_callback;
	inst->request.fork.child_callback_user = child_callback_user;
	inst->request.fork._errno = &_errno;
	sem_post (&inst->request_sem);
	sem_wait (&inst->result_sem);
	errno = _errno;
	return inst->fork_result;
}