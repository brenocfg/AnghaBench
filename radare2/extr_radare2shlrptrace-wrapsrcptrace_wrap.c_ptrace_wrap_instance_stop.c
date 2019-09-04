#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  result_sem; int /*<<< orphan*/  request_sem; int /*<<< orphan*/  th; TYPE_1__ request; } ;
typedef  TYPE_2__ ptrace_wrap_instance ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_WRAP_REQUEST_TYPE_STOP ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

void ptrace_wrap_instance_stop(ptrace_wrap_instance *inst) {
	inst->request.type = PTRACE_WRAP_REQUEST_TYPE_STOP;
	sem_post (&inst->request_sem);
	pthread_join (inst->th, NULL);
	sem_destroy (&inst->request_sem);
	sem_destroy (&inst->result_sem);
}