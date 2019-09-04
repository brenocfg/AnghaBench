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
typedef  enum task_e { ____Placeholder_task_e } task_e ;

/* Variables and functions */
 int TASK_PROCESS ; 
 int /*<<< orphan*/ * pisnd_spi_device ; 
 int /*<<< orphan*/  pisnd_spi_has_more () ; 
 int /*<<< orphan*/  pisnd_work_process ; 
 int /*<<< orphan*/ * pisnd_workqueue ; 
 int /*<<< orphan*/  printd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pisnd_schedule_process(enum task_e task)
{
	if (pisnd_spi_device != NULL &&
		pisnd_workqueue != NULL &&
		!work_pending(&pisnd_work_process)
		) {
		printd("schedule: has more = %d\n", pisnd_spi_has_more());
		if (task == TASK_PROCESS)
			queue_work(pisnd_workqueue, &pisnd_work_process);
	}
}