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
struct riva_par {int FlatPanel; int /*<<< orphan*/  EDID; } ;
struct fb_var_screeninfo {int dummy; } ;
struct TYPE_2__ {int input; int /*<<< orphan*/  modedb_len; int /*<<< orphan*/  modedb; } ;
struct fb_info {TYPE_1__ monspecs; int /*<<< orphan*/  modelist; struct riva_par* par; } ;

/* Variables and functions */
 int FB_DISP_DDI ; 
 int /*<<< orphan*/  fb_edid_to_monspecs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  riva_update_default_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 struct fb_var_screeninfo rivafb_default_var ; 

__attribute__((used)) static void riva_get_edidinfo(struct fb_info *info)
{
	struct fb_var_screeninfo *var = &rivafb_default_var;
	struct riva_par *par = info->par;

	fb_edid_to_monspecs(par->EDID, &info->monspecs);
	fb_videomode_to_modelist(info->monspecs.modedb, info->monspecs.modedb_len,
				 &info->modelist);
	riva_update_default_var(var, info);

	/* if user specified flatpanel, we respect that */
	if (info->monspecs.input & FB_DISP_DDI)
		par->FlatPanel = 1;
}