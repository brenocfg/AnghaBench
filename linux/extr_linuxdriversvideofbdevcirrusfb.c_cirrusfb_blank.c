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
struct fb_info {scalar_t__ state; int /*<<< orphan*/  device; struct cirrusfb_info* par; } ;
struct cirrusfb_info {int blank_mode; int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_GRE ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int vga_rseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int cirrusfb_blank(int blank_mode, struct fb_info *info)
{
	/*
	 * Blank the screen if blank_mode != 0, else unblank. If blank == NULL
	 * then the caller blanks by setting the CLUT (Color Look Up Table)
	 * to all black. Return 0 if blanking succeeded, != 0 if un-/blanking
	 * failed due to e.g. a video mode which doesn't support it.
	 * Implements VESA suspend and powerdown modes on hardware that
	 * supports disabling hsync/vsync:
	 *   blank_mode == 2: suspend vsync
	 *   blank_mode == 3: suspend hsync
	 *   blank_mode == 4: powerdown
	 */
	unsigned char val;
	struct cirrusfb_info *cinfo = info->par;
	int current_mode = cinfo->blank_mode;

	dev_dbg(info->device, "ENTER, blank mode = %d\n", blank_mode);

	if (info->state != FBINFO_STATE_RUNNING ||
	    current_mode == blank_mode) {
		dev_dbg(info->device, "EXIT, returning 0\n");
		return 0;
	}

	/* Undo current */
	if (current_mode == FB_BLANK_NORMAL ||
	    current_mode == FB_BLANK_UNBLANK)
		/* clear "FullBandwidth" bit */
		val = 0;
	else
		/* set "FullBandwidth" bit */
		val = 0x20;

	val |= vga_rseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE) & 0xdf;
	vga_wseq(cinfo->regbase, VGA_SEQ_CLOCK_MODE, val);

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		val = 0x00;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		val = 0x04;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		val = 0x02;
		break;
	case FB_BLANK_POWERDOWN:
		val = 0x06;
		break;
	default:
		dev_dbg(info->device, "EXIT, returning 1\n");
		return 1;
	}

	vga_wgfx(cinfo->regbase, CL_GRE, val);

	cinfo->blank_mode = blank_mode;
	dev_dbg(info->device, "EXIT, returning 0\n");

	/* Let fbcon do a soft blank for us */
	return (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
}