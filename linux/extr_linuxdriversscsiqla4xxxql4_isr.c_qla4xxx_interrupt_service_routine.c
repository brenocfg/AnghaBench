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
typedef  int uint32_t ;
struct scsi_qla_host {TYPE_1__* reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_status; int /*<<< orphan*/ * mailbox; } ;

/* Variables and functions */
 int CSR_SCSI_COMPLETION_INTR ; 
 int CSR_SCSI_PROCESSOR_INTR ; 
 int /*<<< orphan*/  qla4xxx_isr_decode_mailbox (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4xxx_process_response_queue (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rmask (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4xxx_interrupt_service_routine(struct scsi_qla_host * ha,
				       uint32_t intr_status)
{
	/* Process response queue interrupt. */
	if (intr_status & CSR_SCSI_COMPLETION_INTR)
		qla4xxx_process_response_queue(ha);

	/* Process mailbox/asynch event	 interrupt.*/
	if (intr_status & CSR_SCSI_PROCESSOR_INTR) {
		qla4xxx_isr_decode_mailbox(ha,
					   readl(&ha->reg->mailbox[0]));

		/* Clear Mailbox Interrupt */
		writel(set_rmask(CSR_SCSI_PROCESSOR_INTR),
		       &ha->reg->ctrl_status);
		readl(&ha->reg->ctrl_status);
	}
}