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
typedef  void RCoreTask ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 void* r_core_task_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_task_sleep_begin (void*) ; 

__attribute__((used)) static void *r_core_sleep_begin (RCore *core) {
	RCoreTask *task = r_core_task_self (core);
	if (task) {
		r_core_task_sleep_begin (task);
	}
	return task;
}