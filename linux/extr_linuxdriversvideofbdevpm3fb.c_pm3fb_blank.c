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
struct pm3_par {int video; } ;
struct fb_info {struct pm3_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  PM3VideoControl ; 
 int PM3VideoControl_BLANK_ACTIVE_LOW ; 
 int PM3VideoControl_ENABLE ; 
 int PM3VideoControl_HSYNC_ACTIVE_HIGH ; 
 int PM3VideoControl_HSYNC_MASK ; 
 int PM3VideoControl_VSYNC_ACTIVE_HIGH ; 
 int PM3VideoControl_VSYNC_MASK ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm3fb_blank(int blank_mode, struct fb_info *info)
{
	struct pm3_par *par = info->par;
	u32 video = par->video;

	/*
	 * Oxygen VX1 - it appears that setting PM3VideoControl and
	 * then PM3RD_SyncControl to the same SYNC settings undoes
	 * any net change - they seem to xor together.  Only set the
	 * sync options in PM3RD_SyncControl.  --rmk
	 */
	video &= ~(PM3VideoControl_HSYNC_MASK |
		   PM3VideoControl_VSYNC_MASK);
	video |= PM3VideoControl_HSYNC_ACTIVE_HIGH |
		 PM3VideoControl_VSYNC_ACTIVE_HIGH;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		video |= PM3VideoControl_ENABLE;
		break;
	case FB_BLANK_NORMAL:
		video &= ~PM3VideoControl_ENABLE;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		video &= ~(PM3VideoControl_HSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		video &= ~(PM3VideoControl_VSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		break;
	case FB_BLANK_POWERDOWN:
		video &= ~(PM3VideoControl_HSYNC_MASK |
			  PM3VideoControl_VSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		break;
	default:
		DPRINTK("Unsupported blanking %d\n", blank_mode);
		return 1;
	}

	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3VideoControl, video);
	return 0;
}