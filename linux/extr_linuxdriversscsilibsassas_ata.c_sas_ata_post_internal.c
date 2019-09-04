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
struct sas_task {int /*<<< orphan*/ * uldd_task; } ;
struct ata_queued_cmd {int flags; int err_mask; struct sas_task* lldd_task; } ;

/* Variables and functions */
 int AC_ERR_OTHER ; 
 int ATA_QCFLAG_FAILED ; 
 int /*<<< orphan*/  sas_ata_internal_abort (struct sas_task*) ; 

__attribute__((used)) static void sas_ata_post_internal(struct ata_queued_cmd *qc)
{
	if (qc->flags & ATA_QCFLAG_FAILED)
		qc->err_mask |= AC_ERR_OTHER;

	if (qc->err_mask) {
		/*
		 * Find the sas_task and kill it.  By this point, libata
		 * has decided to kill the qc and has frozen the port.
		 * In this state sas_ata_task_done() will no longer free
		 * the sas_task, so we need to notify the lldd (via
		 * ->lldd_abort_task) that the task is dead and free it
		 *  ourselves.
		 */
		struct sas_task *task = qc->lldd_task;

		qc->lldd_task = NULL;
		if (!task)
			return;
		task->uldd_task = NULL;
		sas_ata_internal_abort(task);
	}
}