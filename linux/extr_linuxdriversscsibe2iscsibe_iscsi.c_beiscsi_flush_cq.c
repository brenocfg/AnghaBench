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
typedef  size_t uint16_t ;
struct hwi_controller {struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {struct be_eq_obj* be_eq; } ;
struct beiscsi_hba {size_t num_cpus; struct hwi_controller* phwi_ctrlr; } ;
struct be_eq_obj {int /*<<< orphan*/  iopoll; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_MAX_NUM_CQ_PROC ; 
 int /*<<< orphan*/  beiscsi_process_cq (struct be_eq_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_flush_cq(struct beiscsi_hba *phba)
{
	uint16_t i;
	struct be_eq_obj *pbe_eq;
	struct hwi_controller *phwi_ctrlr;
	struct hwi_context_memory *phwi_context;

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;

	for (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		irq_poll_disable(&pbe_eq->iopoll);
		beiscsi_process_cq(pbe_eq, BE2_MAX_NUM_CQ_PROC);
		irq_poll_enable(&pbe_eq->iopoll);
	}
}