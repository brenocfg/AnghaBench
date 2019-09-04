#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int PALLSW ; 
 int PALMSW ; 
 unsigned int clps_readl (int) ; 
 int /*<<< orphan*/  clps_writel (unsigned int,int) ; 
 scalar_t__ machine_is_edb7211 () ; 

__attribute__((used)) static int
clps7111fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
		     u_int transp, struct fb_info *info)
{
	unsigned int level, mask, shift, pal;

	if (regno >= (1 << info->var.bits_per_pixel))
		return 1;

	/* gray = 0.30*R + 0.58*G + 0.11*B */
	level = (red * 77 + green * 151 + blue * 28) >> 20;

	/*
	 * On an LCD, a high value is dark, while a low value is light. 
	 * So we invert the level.
	 *
	 * This isn't true on all machines, so we only do it on EDB7211.
	 *  --rmk
	 */
	if (machine_is_edb7211()) {
		level = 15 - level;
	}

	shift = 4 * (regno & 7);
	level <<= shift;
	mask  = 15 << shift;
	level &= mask;

	regno = regno < 8 ? PALLSW : PALMSW;

	pal = clps_readl(regno);
	pal = (pal & ~mask) | level;
	clps_writel(pal, regno);

	return 0;
}