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
struct task_struct {int dummy; } ;
struct qla_hw_data {struct task_struct* dpc_thread; int /*<<< orphan*/ * dpc_hp_wq; int /*<<< orphan*/  nic_core_unrecoverable; int /*<<< orphan*/  idc_state_handler; int /*<<< orphan*/  nic_core_reset; int /*<<< orphan*/ * dpc_lp_wq; int /*<<< orphan*/  idc_aen; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 

__attribute__((used)) static void
qla2x00_destroy_deferred_work(struct qla_hw_data *ha)
{
	/* Cancel all work and destroy DPC workqueues */
	if (ha->dpc_lp_wq) {
		cancel_work_sync(&ha->idc_aen);
		destroy_workqueue(ha->dpc_lp_wq);
		ha->dpc_lp_wq = NULL;
	}

	if (ha->dpc_hp_wq) {
		cancel_work_sync(&ha->nic_core_reset);
		cancel_work_sync(&ha->idc_state_handler);
		cancel_work_sync(&ha->nic_core_unrecoverable);
		destroy_workqueue(ha->dpc_hp_wq);
		ha->dpc_hp_wq = NULL;
	}

	/* Kill the kernel thread for this host */
	if (ha->dpc_thread) {
		struct task_struct *t = ha->dpc_thread;

		/*
		 * qla2xxx_wake_dpc checks for ->dpc_thread
		 * so we need to zero it out.
		 */
		ha->dpc_thread = NULL;
		kthread_stop(t);
	}
}