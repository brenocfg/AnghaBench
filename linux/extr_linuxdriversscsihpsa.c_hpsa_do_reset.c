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
typedef  int /*<<< orphan*/  u8 ;
struct hpsa_scsi_dev_t {int /*<<< orphan*/  reset_cmds_out; } ;
struct ctlr_info {int nr_cmds; int /*<<< orphan*/  reset_mutex; TYPE_1__* pdev; int /*<<< orphan*/  event_sync_wait_queue; int /*<<< orphan*/  lock; struct CommandList* cmd_pool; } ;
struct CommandList {struct hpsa_scsi_dev_t* reset_pending; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hpsa_cmd_dev_match (struct ctlr_info*,struct CommandList*,struct hpsa_scsi_dev_t*,unsigned char*) ; 
 int /*<<< orphan*/  hpsa_is_cmd_idle (struct CommandList*) ; 
 int hpsa_send_reset (struct ctlr_info*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int lockup_detected (struct ctlr_info*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_for_device_to_become_ready (struct ctlr_info*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_do_reset(struct ctlr_info *h, struct hpsa_scsi_dev_t *dev,
	unsigned char *scsi3addr, u8 reset_type, int reply_queue)
{
	int i;
	int rc = 0;

	/* We can really only handle one reset at a time */
	if (mutex_lock_interruptible(&h->reset_mutex) == -EINTR) {
		dev_warn(&h->pdev->dev, "concurrent reset wait interrupted.\n");
		return -EINTR;
	}

	BUG_ON(atomic_read(&dev->reset_cmds_out) != 0);

	for (i = 0; i < h->nr_cmds; i++) {
		struct CommandList *c = h->cmd_pool + i;
		int refcount = atomic_inc_return(&c->refcount);

		if (refcount > 1 && hpsa_cmd_dev_match(h, c, dev, scsi3addr)) {
			unsigned long flags;

			/*
			 * Mark the target command as having a reset pending,
			 * then lock a lock so that the command cannot complete
			 * while we're considering it.  If the command is not
			 * idle then count it; otherwise revoke the event.
			 */
			c->reset_pending = dev;
			spin_lock_irqsave(&h->lock, flags);	/* Implied MB */
			if (!hpsa_is_cmd_idle(c))
				atomic_inc(&dev->reset_cmds_out);
			else
				c->reset_pending = NULL;
			spin_unlock_irqrestore(&h->lock, flags);
		}

		cmd_free(h, c);
	}

	rc = hpsa_send_reset(h, scsi3addr, reset_type, reply_queue);
	if (!rc)
		wait_event(h->event_sync_wait_queue,
			atomic_read(&dev->reset_cmds_out) == 0 ||
			lockup_detected(h));

	if (unlikely(lockup_detected(h))) {
		dev_warn(&h->pdev->dev,
			 "Controller lockup detected during reset wait\n");
		rc = -ENODEV;
	}

	if (unlikely(rc))
		atomic_set(&dev->reset_cmds_out, 0);
	else
		rc = wait_for_device_to_become_ready(h, scsi3addr, 0);

	mutex_unlock(&h->reset_mutex);
	return rc;
}