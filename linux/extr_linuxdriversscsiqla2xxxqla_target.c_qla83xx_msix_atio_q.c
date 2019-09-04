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
struct rsp_que {struct qla_hw_data* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  atio_lock; } ;
struct qla_hw_data {TYPE_1__ tgt; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_24xx_process_atio_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

irqreturn_t
qla83xx_msix_atio_q(int irq, void *dev_id)
{
	struct rsp_que *rsp;
	scsi_qla_host_t	*vha;
	struct qla_hw_data *ha;
	unsigned long flags;

	rsp = (struct rsp_que *) dev_id;
	ha = rsp->hw;
	vha = pci_get_drvdata(ha->pdev);

	spin_lock_irqsave(&ha->tgt.atio_lock, flags);

	qlt_24xx_process_atio_queue(vha, 0);

	spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);

	return IRQ_HANDLED;
}