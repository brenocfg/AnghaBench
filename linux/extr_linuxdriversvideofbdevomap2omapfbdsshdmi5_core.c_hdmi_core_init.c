#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  interlace; scalar_t__ vbp; scalar_t__ vfp; scalar_t__ vsw; int /*<<< orphan*/  y_res; int /*<<< orphan*/  vsync_level; scalar_t__ hfp; scalar_t__ hbp; scalar_t__ hsw; int /*<<< orphan*/  x_res; int /*<<< orphan*/  hsync_level; } ;
struct TYPE_5__ {TYPE_1__ timings; int /*<<< orphan*/  hdmi_dvi_mode; } ;
struct hdmi_core_vid_config {int data_enable_pol; TYPE_2__ v_fc_config; scalar_t__ vblank; scalar_t__ vblank_osc; scalar_t__ hblank; } ;
struct TYPE_6__ {int /*<<< orphan*/  interlace; scalar_t__ vbp; scalar_t__ vfp; scalar_t__ vsw; int /*<<< orphan*/  y_res; int /*<<< orphan*/  vsync_level; scalar_t__ hsw; scalar_t__ hbp; scalar_t__ hfp; int /*<<< orphan*/  x_res; int /*<<< orphan*/  hsync_level; } ;
struct hdmi_config {TYPE_3__ timings; int /*<<< orphan*/  hdmi_dvi_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 

__attribute__((used)) static void hdmi_core_init(struct hdmi_core_vid_config *video_cfg,
			struct hdmi_config *cfg)
{
	DSSDBG("hdmi_core_init\n");

	/* video core */
	video_cfg->data_enable_pol = 1; /* It is always 1*/
	video_cfg->v_fc_config.timings.hsync_level = cfg->timings.hsync_level;
	video_cfg->v_fc_config.timings.x_res = cfg->timings.x_res;
	video_cfg->v_fc_config.timings.hsw = cfg->timings.hsw - 1;
	video_cfg->v_fc_config.timings.hbp = cfg->timings.hbp;
	video_cfg->v_fc_config.timings.hfp = cfg->timings.hfp;
	video_cfg->hblank = cfg->timings.hfp +
				cfg->timings.hbp + cfg->timings.hsw - 1;
	video_cfg->v_fc_config.timings.vsync_level = cfg->timings.vsync_level;
	video_cfg->v_fc_config.timings.y_res = cfg->timings.y_res;
	video_cfg->v_fc_config.timings.vsw = cfg->timings.vsw;
	video_cfg->v_fc_config.timings.vfp = cfg->timings.vfp;
	video_cfg->v_fc_config.timings.vbp = cfg->timings.vbp;
	video_cfg->vblank_osc = 0; /* Always 0 - need to confirm */
	video_cfg->vblank = cfg->timings.vsw +
				cfg->timings.vfp + cfg->timings.vbp;
	video_cfg->v_fc_config.hdmi_dvi_mode = cfg->hdmi_dvi_mode;
	video_cfg->v_fc_config.timings.interlace = cfg->timings.interlace;
}