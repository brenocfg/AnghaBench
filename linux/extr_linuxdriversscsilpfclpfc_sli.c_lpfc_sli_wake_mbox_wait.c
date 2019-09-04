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
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
struct completion {int dummy; } ;
struct TYPE_3__ {scalar_t__ context3; int /*<<< orphan*/  mbox_flag; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_MBX_WAKE ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
lpfc_sli_wake_mbox_wait(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmboxq)
{
	unsigned long drvr_flag;
	struct completion *pmbox_done;

	/*
	 * If pmbox_done is empty, the driver thread gave up waiting and
	 * continued running.
	 */
	pmboxq->mbox_flag |= LPFC_MBX_WAKE;
	spin_lock_irqsave(&phba->hbalock, drvr_flag);
	pmbox_done = (struct completion *)pmboxq->context3;
	if (pmbox_done)
		complete(pmbox_done);
	spin_unlock_irqrestore(&phba->hbalock, drvr_flag);
	return;
}