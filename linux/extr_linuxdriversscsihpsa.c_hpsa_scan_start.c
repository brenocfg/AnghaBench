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
struct ctlr_info {int scan_waiting; int drv_req_rescan; int /*<<< orphan*/  reset_lock; scalar_t__ reset_in_progress; int /*<<< orphan*/  scan_lock; scalar_t__ scan_finished; int /*<<< orphan*/  scan_wait_queue; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 void hpsa_scan_complete (struct ctlr_info*) ; 
 int /*<<< orphan*/  hpsa_update_scsi_devices (struct ctlr_info*) ; 
 int /*<<< orphan*/  lockup_detected (struct ctlr_info*) ; 
 struct ctlr_info* shost_to_hba (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hpsa_scan_start(struct Scsi_Host *sh)
{
	struct ctlr_info *h = shost_to_hba(sh);
	unsigned long flags;

	/*
	 * Don't let rescans be initiated on a controller known to be locked
	 * up.  If the controller locks up *during* a rescan, that thread is
	 * probably hosed, but at least we can prevent new rescan threads from
	 * piling up on a locked up controller.
	 */
	if (unlikely(lockup_detected(h)))
		return hpsa_scan_complete(h);

	/*
	 * If a scan is already waiting to run, no need to add another
	 */
	spin_lock_irqsave(&h->scan_lock, flags);
	if (h->scan_waiting) {
		spin_unlock_irqrestore(&h->scan_lock, flags);
		return;
	}

	spin_unlock_irqrestore(&h->scan_lock, flags);

	/* wait until any scan already in progress is finished. */
	while (1) {
		spin_lock_irqsave(&h->scan_lock, flags);
		if (h->scan_finished)
			break;
		h->scan_waiting = 1;
		spin_unlock_irqrestore(&h->scan_lock, flags);
		wait_event(h->scan_wait_queue, h->scan_finished);
		/* Note: We don't need to worry about a race between this
		 * thread and driver unload because the midlayer will
		 * have incremented the reference count, so unload won't
		 * happen if we're in here.
		 */
	}
	h->scan_finished = 0; /* mark scan as in progress */
	h->scan_waiting = 0;
	spin_unlock_irqrestore(&h->scan_lock, flags);

	if (unlikely(lockup_detected(h)))
		return hpsa_scan_complete(h);

	/*
	 * Do the scan after a reset completion
	 */
	spin_lock_irqsave(&h->reset_lock, flags);
	if (h->reset_in_progress) {
		h->drv_req_rescan = 1;
		spin_unlock_irqrestore(&h->reset_lock, flags);
		hpsa_scan_complete(h);
		return;
	}
	spin_unlock_irqrestore(&h->reset_lock, flags);

	hpsa_update_scsi_devices(h);

	hpsa_scan_complete(h);
}