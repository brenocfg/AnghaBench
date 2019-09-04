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
struct fb_info {int dummy; } ;
struct TYPE_2__ {int tt_shiftmode; } ;

/* Variables and functions */
 int TT_SHIFTER_MODEMASK ; 
 int TT_SHIFTER_STHIGH ; 
 TYPE_1__ shifter_tt ; 
 unsigned int* tt_palette ; 

__attribute__((used)) static int tt_setcolreg(unsigned int regno, unsigned int red,
			unsigned int green, unsigned int blue,
			unsigned int transp, struct fb_info *info)
{
	if ((shifter_tt.tt_shiftmode & TT_SHIFTER_MODEMASK) == TT_SHIFTER_STHIGH)
		regno += 254;
	if (regno > 255)
		return 1;
	tt_palette[regno] = (((red >> 12) << 8) | ((green >> 12) << 4) |
			     (blue >> 12));
	if ((shifter_tt.tt_shiftmode & TT_SHIFTER_MODEMASK) ==
	    TT_SHIFTER_STHIGH && regno == 254)
		tt_palette[0] = 0;
	return 0;
}