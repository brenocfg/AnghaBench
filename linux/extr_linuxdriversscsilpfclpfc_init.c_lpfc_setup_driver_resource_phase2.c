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
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/ * wq; int /*<<< orphan*/  worker_thread; int /*<<< orphan*/  brd_no; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/ * alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct lpfc_hba*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_do_work ; 

__attribute__((used)) static int
lpfc_setup_driver_resource_phase2(struct lpfc_hba *phba)
{
	int error;

	/* Startup the kernel thread for this host adapter. */
	phba->worker_thread = kthread_run(lpfc_do_work, phba,
					  "lpfc_worker_%d", phba->brd_no);
	if (IS_ERR(phba->worker_thread)) {
		error = PTR_ERR(phba->worker_thread);
		return error;
	}

	/* The lpfc_wq workqueue for deferred irq use, is only used for SLI4 */
	if (phba->sli_rev == LPFC_SLI_REV4)
		phba->wq = alloc_workqueue("lpfc_wq", WQ_MEM_RECLAIM, 0);
	else
		phba->wq = NULL;

	return 0;
}