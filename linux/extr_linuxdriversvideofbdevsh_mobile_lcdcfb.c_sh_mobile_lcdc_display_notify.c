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
struct TYPE_3__ {int width; int height; } ;
struct sh_mobile_lcdc_chan {TYPE_1__ display; struct fb_info* info; } ;
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_monspecs {int max_x; int max_y; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_info {TYPE_2__ var; int /*<<< orphan*/  state; } ;
typedef  enum sh_mobile_lcdc_entity_event { ____Placeholder_sh_mobile_lcdc_entity_event } sh_mobile_lcdc_entity_event ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_STATE_RUNNING ; 
#define  SH_MOBILE_LCDC_EVENT_DISPLAY_CONNECT 130 
#define  SH_MOBILE_LCDC_EVENT_DISPLAY_DISCONNECT 129 
#define  SH_MOBILE_LCDC_EVENT_DISPLAY_MODE 128 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_set_suspend (struct fb_info*,int) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int sh_mobile_lcdc_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_display_on (struct sh_mobile_lcdc_chan*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_must_reconfigure (struct sh_mobile_lcdc_chan*,struct fb_videomode const*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static int sh_mobile_lcdc_display_notify(struct sh_mobile_lcdc_chan *ch,
					 enum sh_mobile_lcdc_entity_event event,
					 const struct fb_videomode *mode,
					 const struct fb_monspecs *monspec)
{
	struct fb_info *info = ch->info;
	struct fb_var_screeninfo var;
	int ret = 0;

	switch (event) {
	case SH_MOBILE_LCDC_EVENT_DISPLAY_CONNECT:
		/* HDMI plug in */
		console_lock();
		if (lock_fb_info(info)) {


			ch->display.width = monspec->max_x * 10;
			ch->display.height = monspec->max_y * 10;

			if (!sh_mobile_lcdc_must_reconfigure(ch, mode) &&
			    info->state == FBINFO_STATE_RUNNING) {
				/* First activation with the default monitor.
				 * Just turn on, if we run a resume here, the
				 * logo disappears.
				 */
				info->var.width = ch->display.width;
				info->var.height = ch->display.height;
				sh_mobile_lcdc_display_on(ch);
			} else {
				/* New monitor or have to wake up */
				fb_set_suspend(info, 0);
			}


			unlock_fb_info(info);
		}
		console_unlock();
		break;

	case SH_MOBILE_LCDC_EVENT_DISPLAY_DISCONNECT:
		/* HDMI disconnect */
		console_lock();
		if (lock_fb_info(info)) {
			fb_set_suspend(info, 1);
			unlock_fb_info(info);
		}
		console_unlock();
		break;

	case SH_MOBILE_LCDC_EVENT_DISPLAY_MODE:
		/* Validate a proposed new mode */
		fb_videomode_to_var(&var, mode);
		var.bits_per_pixel = info->var.bits_per_pixel;
		var.grayscale = info->var.grayscale;
		ret = sh_mobile_lcdc_check_var(&var, info);
		break;
	}

	return ret;
}