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
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  __lpfc_mbox_cmpl_put (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
lpfc_mbox_cmpl_put(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbq)
{
	unsigned long iflag;

	/* This function expects to be called from interrupt context */
	spin_lock_irqsave(&phba->hbalock, iflag);
	__lpfc_mbox_cmpl_put(phba, mbq);
	spin_unlock_irqrestore(&phba->hbalock, iflag);
	return;
}