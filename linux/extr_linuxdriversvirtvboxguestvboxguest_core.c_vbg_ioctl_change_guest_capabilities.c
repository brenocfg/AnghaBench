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
typedef  int u32 ;
struct vbg_session {int /*<<< orphan*/  guest_caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  global_caps; int /*<<< orphan*/  session_caps; } ;
struct TYPE_6__ {int or_mask; int not_mask; } ;
struct TYPE_5__ {TYPE_1__ out; TYPE_3__ in; } ;
struct vbg_ioctl_set_guest_caps {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;
struct vbg_dev {int /*<<< orphan*/  guest_caps_host; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMMDEV_EVENT_VALID_EVENT_MASK ; 
 scalar_t__ vbg_ioctl_chk (int /*<<< orphan*/ *,int,int) ; 
 int vbg_set_session_capabilities (struct vbg_dev*,struct vbg_session*,int,int,int) ; 

__attribute__((used)) static int vbg_ioctl_change_guest_capabilities(struct vbg_dev *gdev,
	     struct vbg_session *session, struct vbg_ioctl_set_guest_caps *caps)
{
	u32 or_mask, not_mask;
	int ret;

	if (vbg_ioctl_chk(&caps->hdr, sizeof(caps->u.in), sizeof(caps->u.out)))
		return -EINVAL;

	or_mask = caps->u.in.or_mask;
	not_mask = caps->u.in.not_mask;

	if ((or_mask | not_mask) & ~VMMDEV_EVENT_VALID_EVENT_MASK)
		return -EINVAL;

	ret = vbg_set_session_capabilities(gdev, session, or_mask, not_mask,
					   false);
	if (ret)
		return ret;

	caps->u.out.session_caps = session->guest_caps;
	caps->u.out.global_caps = gdev->guest_caps_host;

	return 0;
}