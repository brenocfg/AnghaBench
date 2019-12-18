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
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_2__ {int count; int /*<<< orphan*/  exception_port; int /*<<< orphan*/ * flavors; int /*<<< orphan*/ * behaviors; int /*<<< orphan*/ * ports; int /*<<< orphan*/ * masks; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_1__ ex ; 
 scalar_t__ mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  pid_to_task (int) ; 
 scalar_t__ task_set_exception_ports (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xnu_restore_exception_ports (int pid) {
	kern_return_t kr;
	int i;
	task_t task = pid_to_task (pid);
	if (!task)
		return false;
	for (i = 0; i < ex.count; i++) {
		kr = task_set_exception_ports (task, ex.masks[i], ex.ports[i],
					       ex.behaviors[i], ex.flavors[i]);
		if (kr != KERN_SUCCESS) {
			eprintf ("fail to restore exception ports\n");
			return false;
		}
	}
	kr = mach_port_deallocate (mach_task_self (), ex.exception_port);
	if (kr != KERN_SUCCESS) {
		eprintf ("failed to deallocate exception port\n");
		return false;
	}
	return true;
}