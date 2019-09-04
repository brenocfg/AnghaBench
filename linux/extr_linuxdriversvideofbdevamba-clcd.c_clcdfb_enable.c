#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct clcd_fb {int clk_enabled; TYPE_3__* board; TYPE_2__* panel; scalar_t__ off_cntl; scalar_t__ regs; int /*<<< orphan*/  clk; } ;
struct TYPE_5__ {int /*<<< orphan*/  power; } ;
struct TYPE_8__ {TYPE_1__ props; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* enable ) (struct clcd_fb*) ;} ;
struct TYPE_6__ {TYPE_4__* backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTL_LCDEN ; 
 int /*<<< orphan*/  CNTL_LCDPWR ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_4__*) ; 
 int /*<<< orphan*/  clcdfb_sleep (int) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clcdfb_enable(struct clcd_fb *fb, u32 cntl)
{
	/*
	 * Enable the CLCD clock source.
	 */
	if (!fb->clk_enabled) {
		fb->clk_enabled = true;
		clk_enable(fb->clk);
	}

	/*
	 * Bring up by first enabling..
	 */
	cntl |= CNTL_LCDEN;
	writel(cntl, fb->regs + fb->off_cntl);

	clcdfb_sleep(20);

	/*
	 * and now apply power.
	 */
	cntl |= CNTL_LCDPWR;
	writel(cntl, fb->regs + fb->off_cntl);

	/*
	 * Turn on backlight
	 */
	if (fb->panel->backlight) {
		fb->panel->backlight->props.power = FB_BLANK_UNBLANK;
		backlight_update_status(fb->panel->backlight);
	}

	/*
	 * finally, enable the interface.
	 */
	if (fb->board->enable)
		fb->board->enable(fb);
}