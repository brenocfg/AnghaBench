#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vbg_session {scalar_t__ cancel_waiters; } ;
struct TYPE_5__ {scalar_t__ events; } ;
struct TYPE_4__ {scalar_t__ timeout_ms; scalar_t__ events; } ;
struct TYPE_6__ {TYPE_2__ out; TYPE_1__ in; } ;
struct vbg_ioctl_wait_for_events {TYPE_3__ u; int /*<<< orphan*/  hdr; } ;
struct vbg_dev {int /*<<< orphan*/  event_spinlock; int /*<<< orphan*/  event_wq; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ U32_MAX ; 
 long msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vbg_consume_events_locked (struct vbg_dev*,struct vbg_session*,scalar_t__) ; 
 scalar_t__ vbg_ioctl_chk (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vbg_wait_event_cond (struct vbg_dev*,struct vbg_session*,scalar_t__) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int vbg_ioctl_wait_for_events(struct vbg_dev *gdev,
				     struct vbg_session *session,
				     struct vbg_ioctl_wait_for_events *wait)
{
	u32 timeout_ms = wait->u.in.timeout_ms;
	u32 event_mask = wait->u.in.events;
	unsigned long flags;
	long timeout;
	int ret = 0;

	if (vbg_ioctl_chk(&wait->hdr, sizeof(wait->u.in), sizeof(wait->u.out)))
		return -EINVAL;

	if (timeout_ms == U32_MAX)
		timeout = MAX_SCHEDULE_TIMEOUT;
	else
		timeout = msecs_to_jiffies(timeout_ms);

	wait->u.out.events = 0;
	do {
		timeout = wait_event_interruptible_timeout(
				gdev->event_wq,
				vbg_wait_event_cond(gdev, session, event_mask),
				timeout);

		spin_lock_irqsave(&gdev->event_spinlock, flags);

		if (timeout < 0 || session->cancel_waiters) {
			ret = -EINTR;
		} else if (timeout == 0) {
			ret = -ETIMEDOUT;
		} else {
			wait->u.out.events =
			   vbg_consume_events_locked(gdev, session, event_mask);
		}

		spin_unlock_irqrestore(&gdev->event_spinlock, flags);

		/*
		 * Someone else may have consumed the event(s) first, in
		 * which case we go back to waiting.
		 */
	} while (ret == 0 && wait->u.out.events == 0);

	return ret;
}