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
struct lpfc_sli {int /*<<< orphan*/  sli_flag; scalar_t__ mbox_active; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; struct lpfc_sli sli; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_SLI_ASYNC_MBX_BLK ; 
 unsigned long jiffies ; 
 int lpfc_mbox_tmo_val (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_process_missed_mbox_completions (struct lpfc_hba*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int
lpfc_sli4_async_mbox_block(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	int rc = 0;
	unsigned long timeout = 0;

	/* Mark the asynchronous mailbox command posting as blocked */
	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_SLI_ASYNC_MBX_BLK;
	/* Determine how long we might wait for the active mailbox
	 * command to be gracefully completed by firmware.
	 */
	if (phba->sli.mbox_active)
		timeout = msecs_to_jiffies(lpfc_mbox_tmo_val(phba,
						phba->sli.mbox_active) *
						1000) + jiffies;
	spin_unlock_irq(&phba->hbalock);

	/* Make sure the mailbox is really active */
	if (timeout)
		lpfc_sli4_process_missed_mbox_completions(phba);

	/* Wait for the outstnading mailbox command to complete */
	while (phba->sli.mbox_active) {
		/* Check active mailbox complete status every 2ms */
		msleep(2);
		if (time_after(jiffies, timeout)) {
			/* Timeout, marked the outstanding cmd not complete */
			rc = 1;
			break;
		}
	}

	/* Can not cleanly block async mailbox command, fails it */
	if (rc) {
		spin_lock_irq(&phba->hbalock);
		psli->sli_flag &= ~LPFC_SLI_ASYNC_MBX_BLK;
		spin_unlock_irq(&phba->hbalock);
	}
	return rc;
}