#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct clcd_regs {int pixclock; int /*<<< orphan*/  cntl; int /*<<< orphan*/  tim3; int /*<<< orphan*/  tim2; int /*<<< orphan*/  tim1; int /*<<< orphan*/  tim0; } ;
struct TYPE_7__ {int line_length; int /*<<< orphan*/  visual; } ;
struct TYPE_6__ {int xres_virtual; int bits_per_pixel; } ;
struct TYPE_8__ {TYPE_2__ fix; TYPE_1__ var; } ;
struct clcd_fb {int clk_enabled; int /*<<< orphan*/  clcd_cntl; int /*<<< orphan*/  clk; scalar_t__ regs; TYPE_5__* vendor; TYPE_4__* board; TYPE_3__ fb; } ;
struct TYPE_10__ {scalar_t__ clock_timregs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* decode ) (struct clcd_fb*,struct clcd_regs*) ;} ;

/* Variables and functions */
 scalar_t__ CLCD_TIM0 ; 
 scalar_t__ CLCD_TIM1 ; 
 scalar_t__ CLCD_TIM2 ; 
 scalar_t__ CLCD_TIM3 ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  clcdfb_disable (struct clcd_fb*) ; 
 int /*<<< orphan*/  clcdfb_enable (struct clcd_fb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clcdfb_set_start (struct clcd_fb*) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*,struct clcd_regs*) ; 
 struct clcd_fb* to_clcd (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clcdfb_set_par(struct fb_info *info)
{
	struct clcd_fb *fb = to_clcd(info);
	struct clcd_regs regs;

	fb->fb.fix.line_length = fb->fb.var.xres_virtual *
				 fb->fb.var.bits_per_pixel / 8;

	if (fb->fb.var.bits_per_pixel <= 8)
		fb->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	else
		fb->fb.fix.visual = FB_VISUAL_TRUECOLOR;

	fb->board->decode(fb, &regs);

	clcdfb_disable(fb);

	/* Some variants must be clocked here */
	if (fb->vendor->clock_timregs && !fb->clk_enabled) {
		fb->clk_enabled = true;
		clk_enable(fb->clk);
	}

	writel(regs.tim0, fb->regs + CLCD_TIM0);
	writel(regs.tim1, fb->regs + CLCD_TIM1);
	writel(regs.tim2, fb->regs + CLCD_TIM2);
	writel(regs.tim3, fb->regs + CLCD_TIM3);

	clcdfb_set_start(fb);

	clk_set_rate(fb->clk, (1000000000 / regs.pixclock) * 1000);

	fb->clcd_cntl = regs.cntl;

	clcdfb_enable(fb, regs.cntl);

#ifdef DEBUG
	printk(KERN_INFO
	       "CLCD: Registers set to\n"
	       "  %08x %08x %08x %08x\n"
	       "  %08x %08x %08x %08x\n",
		readl(fb->regs + CLCD_TIM0), readl(fb->regs + CLCD_TIM1),
		readl(fb->regs + CLCD_TIM2), readl(fb->regs + CLCD_TIM3),
		readl(fb->regs + CLCD_UBAS), readl(fb->regs + CLCD_LBAS),
		readl(fb->regs + fb->off_ienb), readl(fb->regs + fb->off_cntl));
#endif

	return 0;
}