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
struct qlogicpti {int /*<<< orphan*/  qhost; scalar_t__ sreg; scalar_t__ is_pti; scalar_t__ qregs; int /*<<< orphan*/  req_dvma; int /*<<< orphan*/  req_cpu; int /*<<< orphan*/  res_dvma; int /*<<< orphan*/  res_cpu; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
typedef  int RES_QUEUE_LEN ;
typedef  int QLOGICPTI_REQ_QUEUE_LEN ;

/* Variables and functions */
 int QUEUE_ENTRY_LEN ; 
 scalar_t__ SBUS_CTRL ; 
 struct qlogicpti* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qlogicpti*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  qpti_chain_del (struct qlogicpti*) ; 
 int resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbus_writew (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qpti_sbus_remove(struct platform_device *op)
{
	struct qlogicpti *qpti = dev_get_drvdata(&op->dev);

	qpti_chain_del(qpti);

	scsi_remove_host(qpti->qhost);

	/* Shut up the card. */
	sbus_writew(0, qpti->qregs + SBUS_CTRL);

	/* Free IRQ handler and unmap Qlogic,ISP and PTI status regs. */
	free_irq(qpti->irq, qpti);

#define QSIZE(entries)	(((entries) + 1) * QUEUE_ENTRY_LEN)
	dma_free_coherent(&op->dev,
			  QSIZE(RES_QUEUE_LEN),
			  qpti->res_cpu, qpti->res_dvma);
	dma_free_coherent(&op->dev,
			  QSIZE(QLOGICPTI_REQ_QUEUE_LEN),
			  qpti->req_cpu, qpti->req_dvma);
#undef QSIZE

	of_iounmap(&op->resource[0], qpti->qregs,
		   resource_size(&op->resource[0]));
	if (qpti->is_pti)
		of_iounmap(&op->resource[0], qpti->sreg, sizeof(unsigned char));

	scsi_host_put(qpti->qhost);

	return 0;
}