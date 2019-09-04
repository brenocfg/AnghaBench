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
typedef  int u32 ;
struct pm2fb_par {int video; } ;
struct fb_info {struct pm2fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int PM2F_BLANK_LOW ; 
 int PM2F_HSYNC_MASK ; 
 int PM2F_VIDEO_ENABLE ; 
 int PM2F_VSYNC_MASK ; 
 int /*<<< orphan*/  set_video (struct pm2fb_par*,int) ; 

__attribute__((used)) static int pm2fb_blank(int blank_mode, struct fb_info *info)
{
	struct pm2fb_par *par = info->par;
	u32 video = par->video;

	DPRINTK("blank_mode %d\n", blank_mode);

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		/* Screen: On */
		video |= PM2F_VIDEO_ENABLE;
		break;
	case FB_BLANK_NORMAL:
		/* Screen: Off */
		video &= ~PM2F_VIDEO_ENABLE;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		/* VSync: Off */
		video &= ~(PM2F_VSYNC_MASK | PM2F_BLANK_LOW);
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		/* HSync: Off */
		video &= ~(PM2F_HSYNC_MASK | PM2F_BLANK_LOW);
		break;
	case FB_BLANK_POWERDOWN:
		/* HSync: Off, VSync: Off */
		video &= ~(PM2F_VSYNC_MASK | PM2F_HSYNC_MASK | PM2F_BLANK_LOW);
		break;
	}
	set_video(par, video);
	return 0;
}