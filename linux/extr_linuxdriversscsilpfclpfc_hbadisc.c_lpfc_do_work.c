#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hba {int /*<<< orphan*/ * worker_thread; scalar_t__ data_flags; int /*<<< orphan*/  work_waitq; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DATA_READY ; 
 int /*<<< orphan*/  MIN_NICE ; 
 int /*<<< orphan*/  PF_NOFREEZE ; 
 TYPE_1__* current ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_work_done (struct lpfc_hba*) ; 
 int /*<<< orphan*/  set_user_nice (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int
lpfc_do_work(void *p)
{
	struct lpfc_hba *phba = p;
	int rc;

	set_user_nice(current, MIN_NICE);
	current->flags |= PF_NOFREEZE;
	phba->data_flags = 0;

	while (!kthread_should_stop()) {
		/* wait and check worker queue activities */
		rc = wait_event_interruptible(phba->work_waitq,
					(test_and_clear_bit(LPFC_DATA_READY,
							    &phba->data_flags)
					 || kthread_should_stop()));
		/* Signal wakeup shall terminate the worker thread */
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_ELS,
					"0433 Wakeup on signal: rc=x%x\n", rc);
			break;
		}

		/* Attend pending lpfc data processing */
		lpfc_work_done(phba);
	}
	phba->worker_thread = NULL;
	lpfc_printf_log(phba, KERN_INFO, LOG_ELS,
			"0432 Worker thread stopped.\n");
	return 0;
}