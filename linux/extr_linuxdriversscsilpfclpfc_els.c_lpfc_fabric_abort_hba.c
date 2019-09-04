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
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  fabric_iocb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOERR_SLI_ABORTED ; 
 int /*<<< orphan*/  IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completions ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli_cancel_iocbs (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void lpfc_fabric_abort_hba(struct lpfc_hba *phba)
{
	LIST_HEAD(completions);

	spin_lock_irq(&phba->hbalock);
	list_splice_init(&phba->fabric_iocb_list, &completions);
	spin_unlock_irq(&phba->hbalock);

	/* Cancel all the IOCBs from the completions list */
	lpfc_sli_cancel_iocbs(phba, &completions, IOSTAT_LOCAL_REJECT,
			      IOERR_SLI_ABORTED);
}