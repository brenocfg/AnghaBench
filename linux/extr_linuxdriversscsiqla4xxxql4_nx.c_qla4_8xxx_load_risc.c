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
struct scsi_qla_host {int /*<<< orphan*/  flags; TYPE_1__* qla4_82xx_reg; TYPE_2__* qla4_83xx_reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  risc_intr; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IRQ_ATTACHED ; 
 int QLA_SUCCESS ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8042 (struct scsi_qla_host*) ; 
 int qla4_8xxx_device_state_handler (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_init_rings (struct scsi_qla_host*) ; 
 int qla4xxx_request_irqs (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qla4_8xxx_load_risc(struct scsi_qla_host *ha)
{
	int retval;

	/* clear the interrupt */
	if (is_qla8032(ha) || is_qla8042(ha)) {
		writel(0, &ha->qla4_83xx_reg->risc_intr);
		readl(&ha->qla4_83xx_reg->risc_intr);
	} else if (is_qla8022(ha)) {
		writel(0, &ha->qla4_82xx_reg->host_int);
		readl(&ha->qla4_82xx_reg->host_int);
	}

	retval = qla4_8xxx_device_state_handler(ha);

	/* Initialize request and response queues. */
	if (retval == QLA_SUCCESS)
		qla4xxx_init_rings(ha);

	if (retval == QLA_SUCCESS && !test_bit(AF_IRQ_ATTACHED, &ha->flags))
		retval = qla4xxx_request_irqs(ha);

	return retval;
}