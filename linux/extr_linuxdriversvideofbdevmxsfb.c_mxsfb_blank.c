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
struct mxsfb_info {int /*<<< orphan*/  enabled; } ;
struct fb_info {struct mxsfb_info* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  mxsfb_disable_controller (struct fb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_controller (struct fb_info*) ; 

__attribute__((used)) static int mxsfb_blank(int blank, struct fb_info *fb_info)
{
	struct mxsfb_info *host = fb_info->par;

	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		if (host->enabled)
			mxsfb_disable_controller(fb_info);
		break;

	case FB_BLANK_UNBLANK:
		if (!host->enabled)
			mxsfb_enable_controller(fb_info);
		break;
	}
	return 0;
}