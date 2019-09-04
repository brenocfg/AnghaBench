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
typedef  int u32 ;
struct vbg_session {scalar_t__ cancel_waiters; } ;
struct vbg_dev {int pending_events; int /*<<< orphan*/  event_spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool vbg_wait_event_cond(struct vbg_dev *gdev,
				struct vbg_session *session,
				u32 event_mask)
{
	unsigned long flags;
	bool wakeup;
	u32 events;

	spin_lock_irqsave(&gdev->event_spinlock, flags);

	events = gdev->pending_events & event_mask;
	wakeup = events || session->cancel_waiters;

	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	return wakeup;
}