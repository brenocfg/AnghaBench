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
struct fb_videomode {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_4__ {struct fb_videomode mode; } ;
struct sh_mobile_lcdc_chan {TYPE_2__ display; TYPE_1__* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ fb_mode_is_equal (struct fb_videomode*,struct fb_videomode const*) ; 

__attribute__((used)) static bool
sh_mobile_lcdc_must_reconfigure(struct sh_mobile_lcdc_chan *ch,
				const struct fb_videomode *new_mode)
{
	dev_dbg(ch->info->dev, "Old %ux%u, new %ux%u\n",
		ch->display.mode.xres, ch->display.mode.yres,
		new_mode->xres, new_mode->yres);

	/* It can be a different monitor with an equal video-mode */
	if (fb_mode_is_equal(&ch->display.mode, new_mode))
		return false;

	dev_dbg(ch->info->dev, "Switching %u -> %u lines\n",
		ch->display.mode.yres, new_mode->yres);
	ch->display.mode = *new_mode;

	return true;
}