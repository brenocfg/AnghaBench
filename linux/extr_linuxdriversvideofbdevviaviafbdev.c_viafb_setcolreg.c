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
typedef  int u32 ;
struct viafb_par {scalar_t__ iga_path; } ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_8__ {int length; unsigned int offset; } ;
struct TYPE_7__ {int length; unsigned int offset; } ;
struct TYPE_10__ {TYPE_4__ green; TYPE_3__ blue; TYPE_2__ red; } ;
struct TYPE_6__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_5__ var; TYPE_1__ fix; struct viafb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ IGA1 ; 
 scalar_t__ IGA2 ; 
 int /*<<< orphan*/  viafb_dual_fb ; 
 int /*<<< orphan*/  viafb_set_primary_color_register (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  viafb_set_secondary_color_register (unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int viafb_setcolreg(unsigned regno, unsigned red, unsigned green,
unsigned blue, unsigned transp, struct fb_info *info)
{
	struct viafb_par *viapar = info->par;
	u32 r, g, b;

	if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) {
		if (regno > 255)
			return -EINVAL;

		if (!viafb_dual_fb || viapar->iga_path == IGA1)
			viafb_set_primary_color_register(regno, red >> 8,
				green >> 8, blue >> 8);

		if (!viafb_dual_fb || viapar->iga_path == IGA2)
			viafb_set_secondary_color_register(regno, red >> 8,
				green >> 8, blue >> 8);
	} else {
		if (regno > 15)
			return -EINVAL;

		r = (red >> (16 - info->var.red.length))
			<< info->var.red.offset;
		b = (blue >> (16 - info->var.blue.length))
			<< info->var.blue.offset;
		g = (green >> (16 - info->var.green.length))
			<< info->var.green.offset;
		((u32 *) info->pseudo_palette)[regno] = r | g | b;
	}

	return 0;
}