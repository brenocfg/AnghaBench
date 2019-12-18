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
typedef  int /*<<< orphan*/  RCoreTask ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_task_continue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_core_task_self (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_core_break (RCore *core) {
	// if we are not in the main thread we hold in a lock
	RCoreTask *task = r_core_task_self (core);
	if (task) {
		r_core_task_continue (task);
	}
}