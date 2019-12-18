#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int type; } ;
struct TYPE_8__ {int /*<<< orphan*/  result_sem; TYPE_1__ request; int /*<<< orphan*/  request_sem; } ;
typedef  TYPE_2__ ptrace_wrap_instance ;

/* Variables and functions */
#define  PTRACE_WRAP_REQUEST_TYPE_FORK 131 
#define  PTRACE_WRAP_REQUEST_TYPE_FUNC 130 
#define  PTRACE_WRAP_REQUEST_TYPE_PTRACE 129 
#define  PTRACE_WRAP_REQUEST_TYPE_STOP 128 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_fork (TYPE_2__*) ; 
 int /*<<< orphan*/  wrap_func (TYPE_2__*) ; 
 int /*<<< orphan*/  wrap_ptrace (TYPE_2__*) ; 

__attribute__((used)) static void *th_run(ptrace_wrap_instance *inst) {
	while (1) {
		sem_wait (&inst->request_sem);
		switch (inst->request.type) {
		case PTRACE_WRAP_REQUEST_TYPE_STOP:
			goto stop;
		case PTRACE_WRAP_REQUEST_TYPE_PTRACE:
			wrap_ptrace (inst);
			break;
		case PTRACE_WRAP_REQUEST_TYPE_FORK:
			wrap_fork (inst);
			break;
		case PTRACE_WRAP_REQUEST_TYPE_FUNC:
			wrap_func (inst);
			break;
		}
		sem_post (&inst->result_sem);
	}
stop:
	return NULL;
}