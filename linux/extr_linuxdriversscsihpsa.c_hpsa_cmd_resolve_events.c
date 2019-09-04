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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  reset_cmds_out; } ;
struct ctlr_info {int /*<<< orphan*/  event_sync_wait_queue; int /*<<< orphan*/  lock; } ;
struct CommandList {struct hpsa_scsi_dev_t* reset_pending; int /*<<< orphan*/  scsi_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_CMD_IDLE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_cmd_resolve_events(struct ctlr_info *h,
		struct CommandList *c)
{
	bool do_wake = false;

	/*
	 * Reset c->scsi_cmd here so that the reset handler will know
	 * this command has completed.  Then, check to see if the handler is
	 * waiting for this command, and, if so, wake it.
	 */
	c->scsi_cmd = SCSI_CMD_IDLE;
	mb();	/* Declare command idle before checking for pending events. */
	if (c->reset_pending) {
		unsigned long flags;
		struct hpsa_scsi_dev_t *dev;

		/*
		 * There appears to be a reset pending; lock the lock and
		 * reconfirm.  If so, then decrement the count of outstanding
		 * commands and wake the reset command if this is the last one.
		 */
		spin_lock_irqsave(&h->lock, flags);
		dev = c->reset_pending;		/* Re-fetch under the lock. */
		if (dev && atomic_dec_and_test(&dev->reset_cmds_out))
			do_wake = true;
		c->reset_pending = NULL;
		spin_unlock_irqrestore(&h->lock, flags);
	}

	if (do_wake)
		wake_up_all(&h->event_sync_wait_queue);
}