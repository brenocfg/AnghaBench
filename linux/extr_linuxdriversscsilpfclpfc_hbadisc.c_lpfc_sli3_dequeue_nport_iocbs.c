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
typedef  size_t uint32_t ;
struct lpfc_sli {size_t num_rings; int /*<<< orphan*/ * sli3_ring; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; struct lpfc_sli sli; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lpfc_dequeue_nport_iocbs (struct lpfc_hba*,struct lpfc_nodelist*,int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_sli3_dequeue_nport_iocbs(struct lpfc_hba *phba,
		struct lpfc_nodelist *ndlp, struct list_head *dequeue_list)
{
	struct lpfc_sli *psli = &phba->sli;
	uint32_t i;

	spin_lock_irq(&phba->hbalock);
	for (i = 0; i < psli->num_rings; i++)
		__lpfc_dequeue_nport_iocbs(phba, ndlp, &psli->sli3_ring[i],
						dequeue_list);
	spin_unlock_irq(&phba->hbalock);
}