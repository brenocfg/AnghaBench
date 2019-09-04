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
struct TYPE_6__ {unsigned long smem_start; unsigned long line_length; } ;
struct TYPE_4__ {unsigned long yoffset; int yres; } ;
struct TYPE_5__ {TYPE_3__ fix; TYPE_1__ var; } ;
struct clcd_fb {scalar_t__ regs; TYPE_2__ fb; } ;

/* Variables and functions */
 scalar_t__ CLCD_LBAS ; 
 scalar_t__ CLCD_UBAS ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void clcdfb_set_start(struct clcd_fb *fb)
{
	unsigned long ustart = fb->fb.fix.smem_start;
	unsigned long lstart;

	ustart += fb->fb.var.yoffset * fb->fb.fix.line_length;
	lstart = ustart + fb->fb.var.yres * fb->fb.fix.line_length / 2;

	writel(ustart, fb->regs + CLCD_UBAS);
	writel(lstart, fb->regs + CLCD_LBAS);
}