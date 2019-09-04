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
struct vmmdev_hgcmreq_header {int flags; } ;
struct vbg_dev {int /*<<< orphan*/  event_spinlock; } ;

/* Variables and functions */
 int VMMDEV_HGCM_REQ_DONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool hgcm_req_done(struct vbg_dev *gdev,
			  struct vmmdev_hgcmreq_header *header)
{
	unsigned long flags;
	bool done;

	spin_lock_irqsave(&gdev->event_spinlock, flags);
	done = header->flags & VMMDEV_HGCM_REQ_DONE;
	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	return done;
}