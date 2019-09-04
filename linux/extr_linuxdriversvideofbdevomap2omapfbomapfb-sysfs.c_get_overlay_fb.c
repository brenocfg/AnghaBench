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
struct omapfb_info {int num_overlays; struct omap_overlay** overlays; } ;
struct omapfb2_device {int num_fbs; int /*<<< orphan*/ * fbs; } ;
struct omap_overlay {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct omapfb_info *get_overlay_fb(struct omapfb2_device *fbdev,
		struct omap_overlay *ovl)
{
	int i, t;

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		for (t = 0; t < ofbi->num_overlays; t++) {
			if (ofbi->overlays[t] == ovl)
				return ofbi;
		}
	}

	return NULL;
}