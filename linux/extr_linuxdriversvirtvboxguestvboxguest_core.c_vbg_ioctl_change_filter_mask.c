#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vbg_session {int dummy; } ;
struct TYPE_3__ {int or_mask; int not_mask; } ;
struct TYPE_4__ {TYPE_1__ in; } ;
struct vbg_ioctl_change_filter {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMMDEV_EVENT_VALID_EVENT_MASK ; 
 scalar_t__ vbg_ioctl_chk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vbg_set_session_event_filter (struct vbg_dev*,struct vbg_session*,int,int,int) ; 

__attribute__((used)) static int vbg_ioctl_change_filter_mask(struct vbg_dev *gdev,
					struct vbg_session *session,
					struct vbg_ioctl_change_filter *filter)
{
	u32 or_mask, not_mask;

	if (vbg_ioctl_chk(&filter->hdr, sizeof(filter->u.in), 0))
		return -EINVAL;

	or_mask = filter->u.in.or_mask;
	not_mask = filter->u.in.not_mask;

	if ((or_mask | not_mask) & ~VMMDEV_EVENT_VALID_EVENT_MASK)
		return -EINVAL;

	return vbg_set_session_event_filter(gdev, session, or_mask, not_mask,
					    false);
}