#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sgl_list_lock; int /*<<< orphan*/  lpfc_els_sgl_list; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_free_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sglq_list ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_free_els_sgl_list(struct lpfc_hba *phba)
{
	LIST_HEAD(sglq_list);

	/* Retrieve all els sgls from driver list */
	spin_lock_irq(&phba->hbalock);
	spin_lock(&phba->sli4_hba.sgl_list_lock);
	list_splice_init(&phba->sli4_hba.lpfc_els_sgl_list, &sglq_list);
	spin_unlock(&phba->sli4_hba.sgl_list_lock);
	spin_unlock_irq(&phba->hbalock);

	/* Now free the sgl list */
	lpfc_free_sgl_list(phba, &sglq_list);
}