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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ host_scribble; } ;
struct qlogicpti {TYPE_1__* qhost; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct scsi_cmnd* qlogicpti_intr_handler (struct qlogicpti*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static irqreturn_t qpti_intr(int irq, void *dev_id)
{
	struct qlogicpti *qpti = dev_id;
	unsigned long flags;
	struct scsi_cmnd *dq;

	spin_lock_irqsave(qpti->qhost->host_lock, flags);
	dq = qlogicpti_intr_handler(qpti);

	if (dq != NULL) {
		do {
			struct scsi_cmnd *next;

			next = (struct scsi_cmnd *) dq->host_scribble;
			dq->scsi_done(dq);
			dq = next;
		} while (dq != NULL);
	}
	spin_unlock_irqrestore(qpti->qhost->host_lock, flags);

	return IRQ_HANDLED;
}