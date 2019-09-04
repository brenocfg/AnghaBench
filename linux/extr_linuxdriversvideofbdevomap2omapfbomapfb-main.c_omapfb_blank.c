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
struct omapfb_info {struct omapfb2_device* fbdev; } ;
struct omapfb_display_data {int /*<<< orphan*/  auto_update_work_enabled; int /*<<< orphan*/  update_mode; } ;
struct omapfb2_device {int dummy; } ;
struct omap_dss_device {int caps; TYPE_1__* driver; int /*<<< orphan*/  state; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {int (* enable ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  OMAPFB_AUTO_UPDATE ; 
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_ACTIVE ; 
 int OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 struct omapfb_display_data* get_display_data (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_lock (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_start_auto_update (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_stop_auto_update (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_unlock (struct omapfb2_device*) ; 
 int stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static int omapfb_blank(int blank, struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omap_dss_device *display = fb2display(fbi);
	struct omapfb_display_data *d;
	int r = 0;

	if (!display)
		return -EINVAL;

	omapfb_lock(fbdev);

	d = get_display_data(fbdev, display);

	switch (blank) {
	case FB_BLANK_UNBLANK:
		if (display->state == OMAP_DSS_DISPLAY_ACTIVE)
			goto exit;

		r = display->driver->enable(display);

		if ((display->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE) &&
				d->update_mode == OMAPFB_AUTO_UPDATE &&
				!d->auto_update_work_enabled)
			omapfb_start_auto_update(fbdev, display);

		break;

	case FB_BLANK_NORMAL:
		/* FB_BLANK_NORMAL could be implemented.
		 * Needs DSS additions. */
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_POWERDOWN:
		if (display->state != OMAP_DSS_DISPLAY_ACTIVE)
			goto exit;

		if (d->auto_update_work_enabled)
			omapfb_stop_auto_update(fbdev, display);

		display->driver->disable(display);

		break;

	default:
		r = -EINVAL;
	}

exit:
	omapfb_unlock(fbdev);

	return r;
}