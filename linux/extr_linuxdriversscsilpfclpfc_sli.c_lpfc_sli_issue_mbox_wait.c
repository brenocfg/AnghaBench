#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
struct completion {int dummy; } ;
struct TYPE_4__ {int mbox_flag; int /*<<< orphan*/  mbox_cmpl; struct completion* context3; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int LPFC_MBX_WAKE ; 
 int MBX_BUSY ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_wake_mbox_wait ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

int
lpfc_sli_issue_mbox_wait(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmboxq,
			 uint32_t timeout)
{
	struct completion mbox_done;
	int retval;
	unsigned long flag;

	pmboxq->mbox_flag &= ~LPFC_MBX_WAKE;
	/* setup wake call as IOCB callback */
	pmboxq->mbox_cmpl = lpfc_sli_wake_mbox_wait;

	/* setup context3 field to pass wait_queue pointer to wake function  */
	init_completion(&mbox_done);
	pmboxq->context3 = &mbox_done;
	/* now issue the command */
	retval = lpfc_sli_issue_mbox(phba, pmboxq, MBX_NOWAIT);
	if (retval == MBX_BUSY || retval == MBX_SUCCESS) {
		wait_for_completion_timeout(&mbox_done,
					    msecs_to_jiffies(timeout * 1000));

		spin_lock_irqsave(&phba->hbalock, flag);
		pmboxq->context3 = NULL;
		/*
		 * if LPFC_MBX_WAKE flag is set the mailbox is completed
		 * else do not free the resources.
		 */
		if (pmboxq->mbox_flag & LPFC_MBX_WAKE) {
			retval = MBX_SUCCESS;
		} else {
			retval = MBX_TIMEOUT;
			pmboxq->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		}
		spin_unlock_irqrestore(&phba->hbalock, flag);
	}
	return retval;
}