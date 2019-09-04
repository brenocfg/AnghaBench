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
typedef  int /*<<< orphan*/  u32 ;
struct fb_var_screeninfo {int /*<<< orphan*/  pixclock; } ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 atyfb_get_pixclock(struct fb_var_screeninfo *var,
			      struct atyfb_par *par)
{
	u32 pixclock = var->pixclock;
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	u32 lcd_on_off;
	par->pll.ct.xres = 0;
	if (par->lcd_table != 0) {
		lcd_on_off = aty_ld_lcd(LCD_GEN_CNTL, par);
		if (lcd_on_off & LCD_ON) {
			par->pll.ct.xres = var->xres;
			pixclock = par->lcd_pixclock;
		}
	}
#endif
	return pixclock;
}