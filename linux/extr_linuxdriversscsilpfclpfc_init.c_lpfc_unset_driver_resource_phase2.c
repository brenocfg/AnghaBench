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
struct lpfc_hba {scalar_t__ worker_thread; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 

__attribute__((used)) static void
lpfc_unset_driver_resource_phase2(struct lpfc_hba *phba)
{
	if (phba->wq) {
		flush_workqueue(phba->wq);
		destroy_workqueue(phba->wq);
		phba->wq = NULL;
	}

	/* Stop kernel worker thread */
	if (phba->worker_thread)
		kthread_stop(phba->worker_thread);
}