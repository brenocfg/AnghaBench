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
typedef  scalar_t__ u_int ;
typedef  unsigned int u32 ;
struct s1d13xxxfb_par {int dummy; } ;
struct TYPE_9__ {scalar_t__ offset; } ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_7__ {scalar_t__ offset; } ;
struct TYPE_10__ {TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; scalar_t__ grayscale; } ;
struct TYPE_6__ {int visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_5__ var; TYPE_1__ fix; struct s1d13xxxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int /*<<< orphan*/  S1DREG_LKUP_ADDR ; 
 int /*<<< orphan*/  S1DREG_LKUP_DATA ; 
 scalar_t__ S1D_PALETTE_SIZE ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
s1d13xxxfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			u_int transp, struct fb_info *info)
{
	struct s1d13xxxfb_par *s1dfb = info->par;
	unsigned int pseudo_val;

	if (regno >= S1D_PALETTE_SIZE)
		return -EINVAL;

	dbg("s1d13xxxfb_setcolreg: %d: rgb=%d,%d,%d, tr=%d\n",
		    regno, red, green, blue, transp);

	if (info->var.grayscale)
		red = green = blue = (19595*red + 38470*green + 7471*blue) >> 16;

	switch (info->fix.visual) {
		case FB_VISUAL_TRUECOLOR:
			if (regno >= 16)
				return -EINVAL;

			/* deal with creating pseudo-palette entries */

			pseudo_val  = (red   >> 11) << info->var.red.offset;
			pseudo_val |= (green >> 10) << info->var.green.offset;
			pseudo_val |= (blue  >> 11) << info->var.blue.offset;

			dbg("s1d13xxxfb_setcolreg: pseudo %d, val %08x\n",
				    regno, pseudo_val);

			((u32 *)info->pseudo_palette)[regno] = pseudo_val;

			break;
		case FB_VISUAL_PSEUDOCOLOR:
			s1d13xxxfb_writereg(s1dfb, S1DREG_LKUP_ADDR, regno);
			s1d13xxxfb_writereg(s1dfb, S1DREG_LKUP_DATA, red);
			s1d13xxxfb_writereg(s1dfb, S1DREG_LKUP_DATA, green);
			s1d13xxxfb_writereg(s1dfb, S1DREG_LKUP_DATA, blue);

			break;
		default:
			return -ENOSYS;
	}

	dbg("s1d13xxxfb_setcolreg: done\n");

	return 0;
}