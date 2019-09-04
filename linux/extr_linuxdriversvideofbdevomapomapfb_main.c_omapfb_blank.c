#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omapfb_plane_struct {struct omapfb_device* fbdev; } ;
struct omapfb_device {int /*<<< orphan*/  state; TYPE_1__* ctrl; TYPE_2__* panel; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disable ) (TYPE_2__*) ;int /*<<< orphan*/  (* enable ) (TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* suspend ) () ;int /*<<< orphan*/  (* get_update_mode ) () ;int /*<<< orphan*/  (* resume ) () ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_POWERDOWN 129 
#define  FB_BLANK_UNBLANK 128 
 int /*<<< orphan*/  OMAPFB_ACTIVE ; 
 int /*<<< orphan*/  OMAPFB_MANUAL_UPDATE ; 
 int /*<<< orphan*/  OMAPFB_SUSPENDED ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 int omapfb_update_full_screen (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub5 () ; 

__attribute__((used)) static int omapfb_blank(int blank, struct fb_info *fbi)
{
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	int do_update = 0;
	int r = 0;

	omapfb_rqueue_lock(fbdev);
	switch (blank) {
	case FB_BLANK_UNBLANK:
		if (fbdev->state == OMAPFB_SUSPENDED) {
			if (fbdev->ctrl->resume)
				fbdev->ctrl->resume();
			if (fbdev->panel->enable)
				fbdev->panel->enable(fbdev->panel);
			fbdev->state = OMAPFB_ACTIVE;
			if (fbdev->ctrl->get_update_mode() ==
					OMAPFB_MANUAL_UPDATE)
				do_update = 1;
		}
		break;
	case FB_BLANK_POWERDOWN:
		if (fbdev->state == OMAPFB_ACTIVE) {
			if (fbdev->panel->disable)
				fbdev->panel->disable(fbdev->panel);
			if (fbdev->ctrl->suspend)
				fbdev->ctrl->suspend();
			fbdev->state = OMAPFB_SUSPENDED;
		}
		break;
	default:
		r = -EINVAL;
	}
	omapfb_rqueue_unlock(fbdev);

	if (r == 0 && do_update)
		r = omapfb_update_full_screen(fbi);

	return r;
}