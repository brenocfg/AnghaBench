#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  result_sem; int /*<<< orphan*/  request_sem; int /*<<< orphan*/  th; } ;
typedef  TYPE_1__ ptrace_wrap_instance ;

/* Variables and functions */
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 int sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ th_run ; 

int ptrace_wrap_instance_start(ptrace_wrap_instance *inst) {
	int r = sem_init (&inst->request_sem, 0, 0);
	if (r != 0) {
		return r;
	}

	r = sem_init (&inst->result_sem, 0, 0);
	if (r != 0) {
		sem_destroy (&inst->request_sem);
		return r;
	}

	r = pthread_create (&inst->th, NULL, (void *(*)(void *)) th_run, inst);
	if (r != 0) {
		sem_destroy (&inst->request_sem);
		sem_destroy (&inst->result_sem);
		return r;
	}

	return 0;
}