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
struct gxfb_par {int dummy; } ;
struct fb_info {struct gxfb_par* par; } ;
typedef  int green ;

/* Variables and functions */
 int /*<<< orphan*/  DC_PAL_ADDRESS ; 
 int /*<<< orphan*/  DC_PAL_DATA ; 
 int /*<<< orphan*/  write_dc (struct gxfb_par*,int /*<<< orphan*/ ,int) ; 

void gx_set_hw_palette_reg(struct fb_info *info, unsigned regno,
		unsigned red, unsigned green, unsigned blue)
{
	struct gxfb_par *par = info->par;
	int val;

	/* Hardware palette is in RGB 8-8-8 format. */
	val  = (red   << 8) & 0xff0000;
	val |= (green)      & 0x00ff00;
	val |= (blue  >> 8) & 0x0000ff;

	write_dc(par, DC_PAL_ADDRESS, regno);
	write_dc(par, DC_PAL_DATA, val);
}