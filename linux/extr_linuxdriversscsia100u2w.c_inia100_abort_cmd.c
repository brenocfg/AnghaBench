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
typedef  scalar_t__ u8 ;
struct scsi_cmnd {int dummy; } ;
struct orc_scb {scalar_t__ tag_msg; scalar_t__ status; struct orc_extended_scb* escb; } ;
struct orc_host {int /*<<< orphan*/  allocation_lock; struct orc_scb* scb_virt; } ;
struct orc_extended_scb {struct scsi_cmnd* srb; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ ORC_MAXQUEUE ; 
 int SUCCESS ; 
 scalar_t__ orchid_abort_scb (struct orc_host*,struct orc_scb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int inia100_abort_cmd(struct orc_host * host, struct scsi_cmnd *cmd)
{
	struct orc_extended_scb *escb;
	struct orc_scb *scb;
	u8 i;
	unsigned long flags;

	spin_lock_irqsave(&(host->allocation_lock), flags);

	scb = host->scb_virt;

	/* Walk the queue until we find the SCB that belongs to the command
	   block. This isn't a performance critical path so a walk in the park
	   here does no harm */

	for (i = 0; i < ORC_MAXQUEUE; i++, scb++) {
		escb = scb->escb;
		if (scb->status && escb->srb == cmd) {
			if (scb->tag_msg == 0) {
				goto out;
			} else {
				/* Issue an ABORT to the firmware */
				if (orchid_abort_scb(host, scb)) {
					escb->srb = NULL;
					spin_unlock_irqrestore(&host->allocation_lock, flags);
					return SUCCESS;
				} else
					goto out;
			}
		}
	}
out:
	spin_unlock_irqrestore(&host->allocation_lock, flags);
	return FAILED;
}