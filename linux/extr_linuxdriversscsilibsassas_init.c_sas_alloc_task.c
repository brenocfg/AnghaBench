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
struct sas_task {int /*<<< orphan*/  task_state_flags; int /*<<< orphan*/  task_state_lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_TASK_STATE_PENDING ; 
 struct sas_task* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_task_cache ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct sas_task *sas_alloc_task(gfp_t flags)
{
	struct sas_task *task = kmem_cache_zalloc(sas_task_cache, flags);

	if (task) {
		spin_lock_init(&task->task_state_lock);
		task->task_state_flags = SAS_TASK_STATE_PENDING;
	}

	return task;
}