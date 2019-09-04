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
struct omap_video_timings {scalar_t__ interlace; int /*<<< orphan*/  hsync_level; int /*<<< orphan*/  vsync_level; int /*<<< orphan*/  vsw; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vbp; int /*<<< orphan*/  hsw; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; } ;
struct hdmi_video_format {int y_res; int /*<<< orphan*/  x_res; int /*<<< orphan*/  packing_mode; } ;
struct TYPE_2__ {int y_res; scalar_t__ interlace; int /*<<< orphan*/  hsync_level; int /*<<< orphan*/  vsync_level; int /*<<< orphan*/  vsw; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vbp; int /*<<< orphan*/  hsw; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; int /*<<< orphan*/  x_res; } ;
struct hdmi_config {TYPE_1__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  HDMI_PACK_10b_RGB_YUV444 ; 

void hdmi_wp_init_vid_fmt_timings(struct hdmi_video_format *video_fmt,
		struct omap_video_timings *timings, struct hdmi_config *param)
{
	DSSDBG("Enter hdmi_wp_video_init_format\n");

	video_fmt->packing_mode = HDMI_PACK_10b_RGB_YUV444;
	video_fmt->y_res = param->timings.y_res;
	video_fmt->x_res = param->timings.x_res;
	if (param->timings.interlace)
		video_fmt->y_res /= 2;

	timings->hbp = param->timings.hbp;
	timings->hfp = param->timings.hfp;
	timings->hsw = param->timings.hsw;
	timings->vbp = param->timings.vbp;
	timings->vfp = param->timings.vfp;
	timings->vsw = param->timings.vsw;
	timings->vsync_level = param->timings.vsync_level;
	timings->hsync_level = param->timings.hsync_level;
	timings->interlace = param->timings.interlace;
}