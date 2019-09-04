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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct fb_info {int* pseudo_palette; TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			  unsigned blue, unsigned transp, struct fb_info *info)
{
	u32 *pal = info->pseudo_palette;

	if (regno > 15)
		return -EINVAL;

	pal[regno] = chan_to_field(red, &info->var.red)
		| chan_to_field(green, &info->var.green)
		| chan_to_field(blue, &info->var.blue)
		| chan_to_field(transp, &info->var.transp);

	return 0;
}