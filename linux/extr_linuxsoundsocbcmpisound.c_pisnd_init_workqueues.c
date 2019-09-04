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
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  pisnd_work_handler ; 
 int /*<<< orphan*/  pisnd_work_process ; 
 int /*<<< orphan*/  pisnd_workqueue ; 

__attribute__((used)) static int pisnd_init_workqueues(void)
{
	pisnd_workqueue = create_singlethread_workqueue("pisnd_workqueue");
	INIT_WORK(&pisnd_work_process, pisnd_work_handler);

	return 0;
}