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
struct fb_monspecs {int modedb_len; struct fb_videomode* modedb; } ;
typedef  struct fb_monspecs u8 ;
struct omap_video_timings {int dummy; } ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_videomode {scalar_t__ pixclock; int xres; int vmode; } ;
struct TYPE_2__ {int (* read_edid ) (struct omap_dss_device*,struct fb_monspecs*,int) ;int (* check_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fb_destroy_modedb (struct fb_videomode*) ; 
 int /*<<< orphan*/  fb_edid_to_monspecs (struct fb_monspecs*,struct fb_monspecs*) ; 
 int /*<<< orphan*/  fb_videomode_to_omap_timings (struct fb_videomode*,struct omap_dss_device*,struct omap_video_timings*) ; 
 int /*<<< orphan*/  kfree (struct fb_monspecs*) ; 
 struct fb_monspecs* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct fb_monspecs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct omap_dss_device*,struct fb_monspecs*,int) ; 
 int stub2 (struct omap_dss_device*,struct omap_video_timings*) ; 

__attribute__((used)) static int omapfb_find_best_mode(struct omap_dss_device *display,
		struct omap_video_timings *timings)
{
	struct fb_monspecs *specs;
	u8 *edid;
	int r, i, best_idx, len;

	if (!display->driver->read_edid)
		return -ENODEV;

	len = 0x80 * 2;
	edid = kmalloc(len, GFP_KERNEL);
	if (edid == NULL)
		return -ENOMEM;

	r = display->driver->read_edid(display, edid, len);
	if (r < 0)
		goto err1;

	specs = kzalloc(sizeof(*specs), GFP_KERNEL);
	if (specs == NULL) {
		r = -ENOMEM;
		goto err1;
	}

	fb_edid_to_monspecs(edid, specs);

	best_idx = -1;

	for (i = 0; i < specs->modedb_len; ++i) {
		struct fb_videomode *m;
		struct omap_video_timings t;

		m = &specs->modedb[i];

		if (m->pixclock == 0)
			continue;

		/* skip repeated pixel modes */
		if (m->xres == 2880 || m->xres == 1440)
			continue;

		if (m->vmode & FB_VMODE_INTERLACED ||
				m->vmode & FB_VMODE_DOUBLE)
			continue;

		fb_videomode_to_omap_timings(m, display, &t);

		r = display->driver->check_timings(display, &t);
		if (r == 0) {
			best_idx = i;
			break;
		}
	}

	if (best_idx == -1) {
		r = -ENOENT;
		goto err2;
	}

	fb_videomode_to_omap_timings(&specs->modedb[best_idx], display,
		timings);

	r = 0;

err2:
	fb_destroy_modedb(specs->modedb);
	kfree(specs);
err1:
	kfree(edid);

	return r;
}