#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnic_wq_copy {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_resets; } ;
struct TYPE_5__ {int /*<<< orphan*/  active_fw_reqs; int /*<<< orphan*/  max_fw_reqs; } ;
struct TYPE_7__ {TYPE_2__ reset_stats; TYPE_1__ fw_stats; } ;
struct fnic {scalar_t__* wq_copy_desc_low; TYPE_4__* lport; TYPE_3__ fnic_stats; int /*<<< orphan*/ * wq_copy_lock; int /*<<< orphan*/  in_flight; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  frame_queue; struct vnic_wq_copy* wq_copy; } ;
struct TYPE_8__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FNIC_FLAGS_FWRESET ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SCSI_NO_TAG ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnic_clear_state_flags (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_queue_wq_copy_desc_fw_reset (struct vnic_wq_copy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_set_state_flags (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_wq_copy_descs (struct fnic*,struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vnic_wq_copy_desc_avail (struct vnic_wq_copy*) ; 

int fnic_fw_reset_handler(struct fnic *fnic)
{
	struct vnic_wq_copy *wq = &fnic->wq_copy[0];
	int ret = 0;
	unsigned long flags;

	/* indicate fwreset to io path */
	fnic_set_state_flags(fnic, FNIC_FLAGS_FWRESET);

	skb_queue_purge(&fnic->frame_queue);
	skb_queue_purge(&fnic->tx_queue);

	/* wait for io cmpl */
	while (atomic_read(&fnic->in_flight))
		schedule_timeout(msecs_to_jiffies(1));

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	if (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		free_wq_copy_descs(fnic, wq);

	if (!vnic_wq_copy_desc_avail(wq))
		ret = -EAGAIN;
	else {
		fnic_queue_wq_copy_desc_fw_reset(wq, SCSI_NO_TAG);
		atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
		if (atomic64_read(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
			  atomic64_read(&fnic->fnic_stats.fw_stats.max_fw_reqs))
			atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
				atomic64_read(
				  &fnic->fnic_stats.fw_stats.active_fw_reqs));
	}

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);

	if (!ret) {
		atomic64_inc(&fnic->fnic_stats.reset_stats.fw_resets);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Issued fw reset\n");
	} else {
		fnic_clear_state_flags(fnic, FNIC_FLAGS_FWRESET);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Failed to issue fw reset\n");
	}

	return ret;
}