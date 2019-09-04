#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {int queue_id; TYPE_2__* phba; } ;
struct TYPE_3__ {int /*<<< orphan*/  EQDBregaddr; } ;
struct TYPE_4__ {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int LPFC_EQID_HI_FIELD_SHIFT ; 
 int LPFC_QUEUE_TYPE_EVENT ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_eqci ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_eqid_hi ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_eqid_lo ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_qt ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

inline void
lpfc_sli4_if6_eq_clr_intr(struct lpfc_queue *q)
{
	struct lpfc_register doorbell;

	doorbell.word0 = 0;
	bf_set(lpfc_eqcq_doorbell_eqci, &doorbell, 1);
	bf_set(lpfc_eqcq_doorbell_qt, &doorbell, LPFC_QUEUE_TYPE_EVENT);
	bf_set(lpfc_eqcq_doorbell_eqid_hi, &doorbell,
		(q->queue_id >> LPFC_EQID_HI_FIELD_SHIFT));
	bf_set(lpfc_eqcq_doorbell_eqid_lo, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.EQDBregaddr);
}