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
struct omap_video_timings {int x_res; } ;
struct dsi_data {scalar_t__ mode; int line_buffer_size; struct omap_video_timings timings; int /*<<< orphan*/  pix_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CTRL ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_config_vp_num_line_buffers(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	int num_line_buffers;

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		int bpp = dsi_get_pixel_size(dsi->pix_fmt);
		struct omap_video_timings *timings = &dsi->timings;
		/*
		 * Don't use line buffers if width is greater than the video
		 * port's line buffer size
		 */
		if (dsi->line_buffer_size <= timings->x_res * bpp / 8)
			num_line_buffers = 0;
		else
			num_line_buffers = 2;
	} else {
		/* Use maximum number of line buffers in command mode */
		num_line_buffers = 2;
	}

	/* LINE_BUFFER */
	REG_FLD_MOD(dsidev, DSI_CTRL, num_line_buffers, 13, 12);
}