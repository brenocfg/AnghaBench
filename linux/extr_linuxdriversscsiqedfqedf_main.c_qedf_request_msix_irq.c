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
struct TYPE_4__ {TYPE_1__* msix; int /*<<< orphan*/  used_cnt; } ;
struct qedf_ctx {int num_queues; TYPE_2__ int_info; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/ * fp_array; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu_mask (int) ; 
 int irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_msix_handler ; 
 int /*<<< orphan*/  qedf_sync_free_irqs (struct qedf_ctx*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_request_msix_irq(struct qedf_ctx *qedf)
{
	int i, rc, cpu;

	cpu = cpumask_first(cpu_online_mask);
	for (i = 0; i < qedf->num_queues; i++) {
		rc = request_irq(qedf->int_info.msix[i].vector,
		    qedf_msix_handler, 0, "qedf", &qedf->fp_array[i]);

		if (rc) {
			QEDF_WARN(&(qedf->dbg_ctx), "request_irq failed.\n");
			qedf_sync_free_irqs(qedf);
			return rc;
		}

		qedf->int_info.used_cnt++;
		rc = irq_set_affinity_hint(qedf->int_info.msix[i].vector,
		    get_cpu_mask(cpu));
		cpu = cpumask_next(cpu, cpu_online_mask);
	}

	return 0;
}