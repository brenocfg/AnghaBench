#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct st_hba {TYPE_1__* host; struct st_ccb* ccb; } ;
struct st_ccb {TYPE_2__* cmd; int /*<<< orphan*/ * req; } ;
struct TYPE_5__ {int result; int /*<<< orphan*/  (* scsi_done ) (TYPE_2__*) ;} ;
struct TYPE_4__ {size_t can_queue; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_dma_unmap (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void return_abnormal_state(struct st_hba *hba, int status)
{
	struct st_ccb *ccb;
	unsigned long flags;
	u16 tag;

	spin_lock_irqsave(hba->host->host_lock, flags);
	for (tag = 0; tag < hba->host->can_queue; tag++) {
		ccb = &hba->ccb[tag];
		if (ccb->req == NULL)
			continue;
		ccb->req = NULL;
		if (ccb->cmd) {
			scsi_dma_unmap(ccb->cmd);
			ccb->cmd->result = status << 16;
			ccb->cmd->scsi_done(ccb->cmd);
			ccb->cmd = NULL;
		}
	}
	spin_unlock_irqrestore(hba->host->host_lock, flags);
}