#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * running_sem; } ;
typedef  int /*<<< orphan*/  RThreadSemaphore ;
typedef  TYPE_1__ RCoreTask ;

/* Variables and functions */
 int /*<<< orphan*/  r_th_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_th_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_join(RCoreTask *task) {
	RThreadSemaphore *sem = task->running_sem;
	if (!sem) {
		return;
	}

	r_th_sem_wait (sem);
	r_th_sem_post (sem);
}