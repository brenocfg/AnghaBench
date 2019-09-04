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
typedef  scalar_t__ uint32 ;
struct panel_settings {int mode_clkcontrol; int lcdclk; int mode_screen; int /*<<< orphan*/  mode_fifoctrl; int /*<<< orphan*/  mode_outmask; int /*<<< orphan*/  mode_pwmhi; int /*<<< orphan*/  mode_pwmdiv; int /*<<< orphan*/  mode_verttiming; int /*<<< orphan*/  mode_horztiming; int /*<<< orphan*/  Yres; int /*<<< orphan*/  Xres; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;
struct au1200fb_platdata {int /*<<< orphan*/  (* panel_init ) () ;int /*<<< orphan*/  (* panel_shutdown ) () ;} ;
struct TYPE_4__ {scalar_t__ cursorcolor3; scalar_t__ cursorcolor2; scalar_t__ cursorcolor1; scalar_t__ cursorcolor0; scalar_t__ cursorpos; scalar_t__ cursorctrl; } ;
struct TYPE_6__ {int screen; int intstatus; int clkcontrol; TYPE_1__ hwc; int /*<<< orphan*/  colorkeymsk; int /*<<< orphan*/  colorkey; int /*<<< orphan*/  backcolor; scalar_t__ intenable; scalar_t__ winenable; int /*<<< orphan*/  fifoctrl; int /*<<< orphan*/  outmask; int /*<<< orphan*/  pwmhi; int /*<<< orphan*/  pwmdiv; int /*<<< orphan*/  verttiming; int /*<<< orphan*/  horztiming; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode_colorkeymsk; int /*<<< orphan*/  mode_colorkey; int /*<<< orphan*/  mode_backcolor; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int LCD_CLKCONTROL_EXT ; 
 int LCD_INT_SD ; 
 int LCD_INT_SS ; 
 int LCD_SCREEN_SEN ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 long clk_round_rate (struct clk*,long) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,long) ; 
 TYPE_3__* lcd ; 
 struct panel_settings* panel ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 TYPE_2__* win ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void au1200_setpanel(struct panel_settings *newpanel,
			    struct au1200fb_platdata *pd)
{
	/*
	 * Perform global setup/init of LCD controller
	 */
	uint32 winenable;

	/* Make sure all windows disabled */
	winenable = lcd->winenable;
	lcd->winenable = 0;
	wmb(); /* drain writebuffer */
	/*
	 * Ensure everything is disabled before reconfiguring
	 */
	if (lcd->screen & LCD_SCREEN_SEN) {
		/* Wait for vertical sync period */
		lcd->intstatus = LCD_INT_SS;
		while ((lcd->intstatus & LCD_INT_SS) == 0)
			;

		lcd->screen &= ~LCD_SCREEN_SEN;	/*disable the controller*/

		do {
			lcd->intstatus = lcd->intstatus; /*clear interrupts*/
			wmb(); /* drain writebuffer */
		/*wait for controller to shut down*/
		} while ((lcd->intstatus & LCD_INT_SD) == 0);

		/* Call shutdown of current panel (if up) */
		/* this must occur last, because if an external clock is driving
		    the controller, the clock cannot be turned off before first
			shutting down the controller.
		 */
		if (pd->panel_shutdown)
			pd->panel_shutdown();
	}

	/* Newpanel == NULL indicates a shutdown operation only */
	if (newpanel == NULL)
		return;

	panel = newpanel;

	printk("Panel(%s), %dx%d\n", panel->name, panel->Xres, panel->Yres);

	/*
	 * Setup clocking if internal LCD clock source (assumes sys_auxpll valid)
	 */
	if (!(panel->mode_clkcontrol & LCD_CLKCONTROL_EXT))
	{
		struct clk *c = clk_get(NULL, "lcd_intclk");
		long r, pc = panel->lcdclk * 1000000;

		if (!IS_ERR(c)) {
			r = clk_round_rate(c, pc);
			if ((pc - r) < (pc / 10)) {	/* 10% slack */
				clk_set_rate(c, r);
				clk_prepare_enable(c);
			}
			clk_put(c);
		}
	}

	/*
	 * Configure panel timings
	 */
	lcd->screen = panel->mode_screen;
	lcd->horztiming = panel->mode_horztiming;
	lcd->verttiming = panel->mode_verttiming;
	lcd->clkcontrol = panel->mode_clkcontrol;
	lcd->pwmdiv = panel->mode_pwmdiv;
	lcd->pwmhi = panel->mode_pwmhi;
	lcd->outmask = panel->mode_outmask;
	lcd->fifoctrl = panel->mode_fifoctrl;
	wmb(); /* drain writebuffer */

	/* fixme: Check window settings to make sure still valid
	 * for new geometry */
#if 0
	au1200_setlocation(fbdev, 0, win->w[0].xpos, win->w[0].ypos);
	au1200_setlocation(fbdev, 1, win->w[1].xpos, win->w[1].ypos);
	au1200_setlocation(fbdev, 2, win->w[2].xpos, win->w[2].ypos);
	au1200_setlocation(fbdev, 3, win->w[3].xpos, win->w[3].ypos);
#endif
	lcd->winenable = winenable;

	/*
	 * Re-enable screen now that it is configured
	 */
	lcd->screen |= LCD_SCREEN_SEN;
	wmb(); /* drain writebuffer */

	/* Call init of panel */
	if (pd->panel_init)
		pd->panel_init();

	/* FIX!!!! not appropriate on panel change!!! Global setup/init */
	lcd->intenable = 0;
	lcd->intstatus = ~0;
	lcd->backcolor = win->mode_backcolor;

	/* Setup Color Key - FIX!!! */
	lcd->colorkey = win->mode_colorkey;
	lcd->colorkeymsk = win->mode_colorkeymsk;

	/* Setup HWCursor - FIX!!! Need to support this eventually */
	lcd->hwc.cursorctrl = 0;
	lcd->hwc.cursorpos = 0;
	lcd->hwc.cursorcolor0 = 0;
	lcd->hwc.cursorcolor1 = 0;
	lcd->hwc.cursorcolor2 = 0;
	lcd->hwc.cursorcolor3 = 0;


#if 0
#define D(X) printk("%25s: %08X\n", #X, X)
	D(lcd->screen);
	D(lcd->horztiming);
	D(lcd->verttiming);
	D(lcd->clkcontrol);
	D(lcd->pwmdiv);
	D(lcd->pwmhi);
	D(lcd->outmask);
	D(lcd->fifoctrl);
	D(lcd->window[0].winctrl0);
	D(lcd->window[0].winctrl1);
	D(lcd->window[0].winctrl2);
	D(lcd->window[0].winbuf0);
	D(lcd->window[0].winbuf1);
	D(lcd->window[0].winbufctrl);
	D(lcd->window[1].winctrl0);
	D(lcd->window[1].winctrl1);
	D(lcd->window[1].winctrl2);
	D(lcd->window[1].winbuf0);
	D(lcd->window[1].winbuf1);
	D(lcd->window[1].winbufctrl);
	D(lcd->window[2].winctrl0);
	D(lcd->window[2].winctrl1);
	D(lcd->window[2].winctrl2);
	D(lcd->window[2].winbuf0);
	D(lcd->window[2].winbuf1);
	D(lcd->window[2].winbufctrl);
	D(lcd->window[3].winctrl0);
	D(lcd->window[3].winctrl1);
	D(lcd->window[3].winctrl2);
	D(lcd->window[3].winbuf0);
	D(lcd->window[3].winbuf1);
	D(lcd->window[3].winbufctrl);
	D(lcd->winenable);
	D(lcd->intenable);
	D(lcd->intstatus);
	D(lcd->backcolor);
	D(lcd->winenable);
	D(lcd->colorkey);
    D(lcd->colorkeymsk);
	D(lcd->hwc.cursorctrl);
	D(lcd->hwc.cursorpos);
	D(lcd->hwc.cursorcolor0);
	D(lcd->hwc.cursorcolor1);
	D(lcd->hwc.cursorcolor2);
	D(lcd->hwc.cursorcolor3);
#endif
}