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
typedef  unsigned int u32 ;
struct fb_info {scalar_t__ pseudo_palette; } ;
struct TYPE_2__ {unsigned int* color_reg; } ;

/* Variables and functions */
 unsigned int* f030_col ; 
 TYPE_1__ shifter_tt ; 

__attribute__((used)) static int falcon_setcolreg(unsigned int regno, unsigned int red,
			    unsigned int green, unsigned int blue,
			    unsigned int transp, struct fb_info *info)
{
	if (regno > 255)
		return 1;
	f030_col[regno] = (((red & 0xfc00) << 16) |
			   ((green & 0xfc00) << 8) |
			   ((blue & 0xfc00) >> 8));
	if (regno < 16) {
		shifter_tt.color_reg[regno] =
			(((red & 0xe000) >> 13) | ((red & 0x1000) >> 12) << 8) |
			(((green & 0xe000) >> 13) | ((green & 0x1000) >> 12) << 4) |
			((blue & 0xe000) >> 13) | ((blue & 0x1000) >> 12);
		((u32 *)info->pseudo_palette)[regno] = ((red & 0xf800) |
						       ((green & 0xfc00) >> 5) |
						       ((blue & 0xf800) >> 11));
	}
	return 0;
}