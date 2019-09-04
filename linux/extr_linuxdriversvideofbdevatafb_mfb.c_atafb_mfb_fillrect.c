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
typedef  int u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct fb_info {scalar_t__ screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_memclear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_memclear_small (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_memset255 (int /*<<< orphan*/ *,int) ; 

void atafb_mfb_fillrect(struct fb_info *info, u_long next_line, u32 color,
			int sy, int sx, int height, int width)
{
	u8 *dest;
	u_int rows;

	dest = (u8 *)info->screen_base + sy * next_line + (sx >> 3);

	if (sx == 0 && width == next_line) {
		if (color)
			fb_memset255(dest, height * (width >> 3));
		else
			fb_memclear(dest, height * (width >> 3));
	} else {
		for (rows = height; rows--; dest += next_line) {
			if (color)
				fb_memset255(dest, width >> 3);
			else
				fb_memclear_small(dest, width >> 3);
		}
	}
}