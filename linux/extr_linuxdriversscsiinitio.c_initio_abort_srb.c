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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_ctrl_blk {int flags; scalar_t__ tagmsg; size_t target; struct scsi_ctrl_blk* next; int /*<<< orphan*/  (* post ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;void* hastat; struct scsi_cmnd* srb; } ;
struct scsi_cmnd {int dummy; } ;
struct initio_host {scalar_t__ semaph; int /*<<< orphan*/  semaph_lock; struct scsi_ctrl_blk* last_busy; struct scsi_ctrl_blk* first_busy; int /*<<< orphan*/ * act_tags; struct scsi_ctrl_blk* active; struct scsi_ctrl_blk* last_pending; struct scsi_ctrl_blk* first_pending; scalar_t__ addr; } ;

/* Variables and functions */
 void* HOST_ABORTED ; 
 int SCF_DONE ; 
 int SCF_POST ; 
 int SCSI_ABORT_BUSY ; 
 int SCSI_ABORT_NOT_RUNNING ; 
 int SCSI_ABORT_SNOOZE ; 
 int SCSI_ABORT_SUCCESS ; 
 scalar_t__ TUL_Mask ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tulip_main (struct initio_host*) ; 

__attribute__((used)) static int initio_abort_srb(struct initio_host * host, struct scsi_cmnd *srbp)
{
	unsigned long flags;
	struct scsi_ctrl_blk *tmp, *prev;

	spin_lock_irqsave(&host->semaph_lock, flags);

	if ((host->semaph == 0) && (host->active == NULL)) {
		/* disable Jasmin SCSI Int        */
		outb(0x1F, host->addr + TUL_Mask);
		spin_unlock_irqrestore(&host->semaph_lock, flags);
		/* FIXME: synchronize_irq needed ? */
		tulip_main(host);
		spin_lock_irqsave(&host->semaph_lock, flags);
		host->semaph = 1;
		outb(0x0F, host->addr + TUL_Mask);
		spin_unlock_irqrestore(&host->semaph_lock, flags);
		return SCSI_ABORT_SNOOZE;
	}
	prev = tmp = host->first_pending;	/* Check Pend queue */
	while (tmp != NULL) {
		/* 07/27/98 */
		if (tmp->srb == srbp) {
			if (tmp == host->active) {
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				return SCSI_ABORT_BUSY;
			} else if (tmp == host->first_pending) {
				if ((host->first_pending = tmp->next) == NULL)
					host->last_pending = NULL;
			} else {
				prev->next = tmp->next;
				if (tmp == host->last_pending)
					host->last_pending = prev;
			}
			tmp->hastat = HOST_ABORTED;
			tmp->flags |= SCF_DONE;
			if (tmp->flags & SCF_POST)
				(*tmp->post) ((u8 *) host, (u8 *) tmp);
			spin_unlock_irqrestore(&host->semaph_lock, flags);
			return SCSI_ABORT_SUCCESS;
		}
		prev = tmp;
		tmp = tmp->next;
	}

	prev = tmp = host->first_busy;	/* Check Busy queue */
	while (tmp != NULL) {
		if (tmp->srb == srbp) {
			if (tmp == host->active) {
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				return SCSI_ABORT_BUSY;
			} else if (tmp->tagmsg == 0) {
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				return SCSI_ABORT_BUSY;
			} else {
				host->act_tags[tmp->target]--;
				if (tmp == host->first_busy) {
					if ((host->first_busy = tmp->next) == NULL)
						host->last_busy = NULL;
				} else {
					prev->next = tmp->next;
					if (tmp == host->last_busy)
						host->last_busy = prev;
				}
				tmp->next = NULL;


				tmp->hastat = HOST_ABORTED;
				tmp->flags |= SCF_DONE;
				if (tmp->flags & SCF_POST)
					(*tmp->post) ((u8 *) host, (u8 *) tmp);
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				return SCSI_ABORT_SUCCESS;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	spin_unlock_irqrestore(&host->semaph_lock, flags);
	return SCSI_ABORT_NOT_RUNNING;
}