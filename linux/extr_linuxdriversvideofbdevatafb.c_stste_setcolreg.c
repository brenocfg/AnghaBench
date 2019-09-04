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
struct TYPE_2__ {unsigned int* color_reg; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTD_SHIFTER ; 
 TYPE_1__ shifter_tt ; 

__attribute__((used)) static int stste_setcolreg(unsigned int regno, unsigned int red,
			   unsigned int green, unsigned int blue,
			   unsigned int transp, struct fb_info *info)
{
	if (regno > 15)
		return 1;
	red >>= 12;
	blue >>= 12;
	green >>= 12;
	if (ATARIHW_PRESENT(EXTD_SHIFTER))
		shifter_tt.color_reg[regno] =
			(((red & 0xe) >> 1) | ((red & 1) << 3) << 8) |
			(((green & 0xe) >> 1) | ((green & 1) << 3) << 4) |
			((blue & 0xe) >> 1) | ((blue & 1) << 3);
	else
		shifter_tt.color_reg[regno] =
			((red & 0xe) << 7) |
			((green & 0xe) << 3) |
			((blue & 0xe) >> 1);
	return 0;
}