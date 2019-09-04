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

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shutdown_task ; 
 int /*<<< orphan*/  torture_shutdown_nb ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void torture_shutdown_cleanup(void)
{
	unregister_reboot_notifier(&torture_shutdown_nb);
	if (shutdown_task != NULL) {
		VERBOSE_TOROUT_STRING("Stopping torture_shutdown task");
		kthread_stop(shutdown_task);
	}
	shutdown_task = NULL;
}