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
struct lpfc_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sli4_eq_release ) (struct lpfc_queue*,int /*<<< orphan*/ ) ;} ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_sli4_eq_flush(struct lpfc_hba *phba, struct lpfc_queue *eq)
{
	struct lpfc_eqe *eqe;

	/* walk all the EQ entries and drop on the floor */
	while ((eqe = lpfc_sli4_eq_get(eq)))
		;

	/* Clear and re-arm the EQ */
	phba->sli4_hba.sli4_eq_release(eq, LPFC_QUEUE_REARM);
}