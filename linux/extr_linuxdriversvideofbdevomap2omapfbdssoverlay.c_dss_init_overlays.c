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
struct platform_device {int dummy; } ;
struct omap_overlay {char* name; int /*<<< orphan*/  id; int /*<<< orphan*/  supported_modes; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DSS_GFX ; 
 int /*<<< orphan*/  OMAP_DSS_VIDEO1 ; 
 int /*<<< orphan*/  OMAP_DSS_VIDEO2 ; 
 int /*<<< orphan*/  OMAP_DSS_VIDEO3 ; 
 int dss_feat_get_num_ovls () ; 
 int /*<<< orphan*/  dss_feat_get_overlay_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_feat_get_supported_color_modes (int /*<<< orphan*/ ) ; 
 int dss_overlay_kobj_init (struct omap_overlay*,struct platform_device*) ; 
 struct omap_overlay* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int num_overlays ; 
 struct omap_overlay* overlays ; 

void dss_init_overlays(struct platform_device *pdev)
{
	int i, r;

	num_overlays = dss_feat_get_num_ovls();

	overlays = kcalloc(num_overlays, sizeof(struct omap_overlay),
			   GFP_KERNEL);

	BUG_ON(overlays == NULL);

	for (i = 0; i < num_overlays; ++i) {
		struct omap_overlay *ovl = &overlays[i];

		switch (i) {
		case 0:
			ovl->name = "gfx";
			ovl->id = OMAP_DSS_GFX;
			break;
		case 1:
			ovl->name = "vid1";
			ovl->id = OMAP_DSS_VIDEO1;
			break;
		case 2:
			ovl->name = "vid2";
			ovl->id = OMAP_DSS_VIDEO2;
			break;
		case 3:
			ovl->name = "vid3";
			ovl->id = OMAP_DSS_VIDEO3;
			break;
		}

		ovl->caps = dss_feat_get_overlay_caps(ovl->id);
		ovl->supported_modes =
			dss_feat_get_supported_color_modes(ovl->id);

		r = dss_overlay_kobj_init(ovl, pdev);
		if (r)
			DSSERR("failed to create sysfs file\n");
	}
}