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
typedef  int /*<<< orphan*/  u32 ;
struct sas_task {int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;} ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; } ;
struct pm8001_ccb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 

__attribute__((used)) static inline void
pm8001_ccb_task_free_done(struct pm8001_hba_info *pm8001_ha,
			struct sas_task *task, struct pm8001_ccb_info *ccb,
			u32 ccb_idx)
{
	pm8001_ccb_task_free(pm8001_ha, task, ccb, ccb_idx);
	smp_mb(); /*in order to force CPU ordering*/
	spin_unlock(&pm8001_ha->lock);
	task->task_done(task);
	spin_lock(&pm8001_ha->lock);
}