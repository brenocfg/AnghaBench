#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int used_cnt; TYPE_1__* msix; scalar_t__ msix_cnt; } ;
struct qedf_ctx {int /*<<< orphan*/  cdev; TYPE_2__ int_info; int /*<<< orphan*/ * fp_array; } ;
struct TYPE_8__ {TYPE_3__* common; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_fp_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* simd_handler_clean ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_SIMD_HANDLER_NUM ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* qed_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_sync_free_irqs(struct qedf_ctx *qedf)
{
	int i;

	if (qedf->int_info.msix_cnt) {
		for (i = 0; i < qedf->int_info.used_cnt; i++) {
			synchronize_irq(qedf->int_info.msix[i].vector);
			irq_set_affinity_hint(qedf->int_info.msix[i].vector,
			    NULL);
			irq_set_affinity_notifier(qedf->int_info.msix[i].vector,
			    NULL);
			free_irq(qedf->int_info.msix[i].vector,
			    &qedf->fp_array[i]);
		}
	} else
		qed_ops->common->simd_handler_clean(qedf->cdev,
		    QEDF_SIMD_HANDLER_NUM);

	qedf->int_info.used_cnt = 0;
	qed_ops->common->set_fp_int(qedf->cdev, 0);
}