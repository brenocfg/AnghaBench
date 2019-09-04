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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  jzfb_convert_color_to_hw (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jzfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			unsigned blue, unsigned transp, struct fb_info *fb)
{
	uint32_t color;

	if (regno >= 16)
		return -EINVAL;

	color = jzfb_convert_color_to_hw(red, &fb->var.red);
	color |= jzfb_convert_color_to_hw(green, &fb->var.green);
	color |= jzfb_convert_color_to_hw(blue, &fb->var.blue);
	color |= jzfb_convert_color_to_hw(transp, &fb->var.transp);

	((uint32_t *)(fb->pseudo_palette))[regno] = color;

	return 0;
}