#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/ * wq; TYPE_2__* isp_ops; scalar_t__ interrupts_on; } ;
struct TYPE_11__ {scalar_t__ init_done; scalar_t__ online; } ;
struct TYPE_13__ {TYPE_1__ flags; scalar_t__ timer_active; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* disable_intrs ) (struct qla_hw_data*) ;} ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla25xx_delete_queues (TYPE_3__*) ; 
 int /*<<< orphan*/  qla2x00_abort_all_cmds (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qla2x00_free_fcports (TYPE_3__*) ; 
 int /*<<< orphan*/  qla2x00_free_irqs (TYPE_3__*) ; 
 int /*<<< orphan*/  qla2x00_free_queues (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_mem_free (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_stop_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  qla82xx_md_free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*) ; 

__attribute__((used)) static void
qla2x00_free_device(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	qla2x00_abort_all_cmds(vha, DID_NO_CONNECT << 16);

	/* Disable timer */
	if (vha->timer_active)
		qla2x00_stop_timer(vha);

	qla25xx_delete_queues(vha);
	vha->flags.online = 0;

	/* turn-off interrupts on the card */
	if (ha->interrupts_on) {
		vha->flags.init_done = 0;
		ha->isp_ops->disable_intrs(ha);
	}

	qla2x00_free_fcports(vha);

	qla2x00_free_irqs(vha);

	/* Flush the work queue and remove it */
	if (ha->wq) {
		flush_workqueue(ha->wq);
		destroy_workqueue(ha->wq);
		ha->wq = NULL;
	}


	qla2x00_mem_free(ha);

	qla82xx_md_free(vha);

	qla2x00_free_queues(ha);
}