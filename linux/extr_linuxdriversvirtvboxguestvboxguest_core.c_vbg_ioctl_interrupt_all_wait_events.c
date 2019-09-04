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
struct vbg_session {int cancel_waiters; } ;
struct vbg_ioctl_hdr {int size_in; int size_out; } ;
struct vbg_dev {int /*<<< orphan*/  event_wq; int /*<<< orphan*/  event_spinlock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vbg_ioctl_interrupt_all_wait_events(struct vbg_dev *gdev,
					       struct vbg_session *session,
					       struct vbg_ioctl_hdr *hdr)
{
	unsigned long flags;

	if (hdr->size_in != sizeof(*hdr) || hdr->size_out != sizeof(*hdr))
		return -EINVAL;

	spin_lock_irqsave(&gdev->event_spinlock, flags);
	session->cancel_waiters = true;
	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	wake_up(&gdev->event_wq);

	return 0;
}