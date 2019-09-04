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
struct lpfc_iocbq {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;

/* Variables and functions */
 struct lpfc_iocbq* __lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct lpfc_iocbq *
lpfc_sli_get_iocbq(struct lpfc_hba *phba)
{
	struct lpfc_iocbq * iocbq = NULL;
	unsigned long iflags;

	spin_lock_irqsave(&phba->hbalock, iflags);
	iocbq = __lpfc_sli_get_iocbq(phba);
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	return iocbq;
}