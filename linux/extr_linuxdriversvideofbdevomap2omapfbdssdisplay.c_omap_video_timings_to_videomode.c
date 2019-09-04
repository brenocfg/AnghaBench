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
struct videomode {int /*<<< orphan*/  flags; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hback_porch; int /*<<< orphan*/  hactive; int /*<<< orphan*/  pixelclock; } ;
struct omap_video_timings {scalar_t__ hsync_level; scalar_t__ vsync_level; scalar_t__ de_level; scalar_t__ data_pclk_edge; int /*<<< orphan*/  vsw; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vbp; int /*<<< orphan*/  y_res; int /*<<< orphan*/  hsw; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hbp; int /*<<< orphan*/  x_res; int /*<<< orphan*/  pixelclock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_FLAGS_DE_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_DE_LOW ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_HSYNC_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_HSYNC_LOW ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_PIXDATA_NEGEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_VSYNC_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_VSYNC_LOW ; 
 scalar_t__ OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 scalar_t__ OMAPDSS_SIG_ACTIVE_HIGH ; 
 int /*<<< orphan*/  memset (struct videomode*,int /*<<< orphan*/ ,int) ; 

void omap_video_timings_to_videomode(const struct omap_video_timings *ovt,
		struct videomode *vm)
{
	memset(vm, 0, sizeof(*vm));

	vm->pixelclock = ovt->pixelclock;

	vm->hactive = ovt->x_res;
	vm->hback_porch = ovt->hbp;
	vm->hfront_porch = ovt->hfp;
	vm->hsync_len = ovt->hsw;
	vm->vactive = ovt->y_res;
	vm->vback_porch = ovt->vbp;
	vm->vfront_porch = ovt->vfp;
	vm->vsync_len = ovt->vsw;

	if (ovt->hsync_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_HSYNC_HIGH;
	else
		vm->flags |= DISPLAY_FLAGS_HSYNC_LOW;

	if (ovt->vsync_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_VSYNC_HIGH;
	else
		vm->flags |= DISPLAY_FLAGS_VSYNC_LOW;

	if (ovt->de_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_DE_HIGH;
	else
		vm->flags |= DISPLAY_FLAGS_DE_LOW;

	if (ovt->data_pclk_edge == OMAPDSS_DRIVE_SIG_RISING_EDGE)
		vm->flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
	else
		vm->flags |= DISPLAY_FLAGS_PIXDATA_NEGEDGE;
}