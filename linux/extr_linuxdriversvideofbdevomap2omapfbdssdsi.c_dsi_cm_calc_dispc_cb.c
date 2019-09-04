#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_video_timings {unsigned long pixelclock; int hsw; int hfp; int hbp; int vsw; scalar_t__ vbp; scalar_t__ vfp; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; } ;
struct TYPE_3__ {int lck_div; int pck_div; unsigned long lck; unsigned long pck; } ;
struct dsi_clk_calc_ctx {TYPE_2__* config; TYPE_1__ dispc_cinfo; struct omap_video_timings dispc_vm; } ;
struct TYPE_4__ {struct omap_video_timings* timings; } ;

/* Variables and functions */

__attribute__((used)) static bool dsi_cm_calc_dispc_cb(int lckd, int pckd, unsigned long lck,
		unsigned long pck, void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;
	struct omap_video_timings *t = &ctx->dispc_vm;

	ctx->dispc_cinfo.lck_div = lckd;
	ctx->dispc_cinfo.pck_div = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	*t = *ctx->config->timings;
	t->pixelclock = pck;
	t->x_res = ctx->config->timings->x_res;
	t->y_res = ctx->config->timings->y_res;
	t->hsw = t->hfp = t->hbp = t->vsw = 1;
	t->vfp = t->vbp = 0;

	return true;
}