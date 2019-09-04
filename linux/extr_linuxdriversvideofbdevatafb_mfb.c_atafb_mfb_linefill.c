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
typedef  int u32 ;
struct fb_info {scalar_t__ screen_base; } ;

/* Variables and functions */

void atafb_mfb_linefill(struct fb_info *info, u_long next_line,
			int dy, int dx, u32 width,
			const u8 *data, u32 bgcolor, u32 fgcolor)
{
	u8 *dest;
	u_int rows;

	dest = (u8 *)info->screen_base + dy * next_line + (dx >> 3);

	for (rows = width / 8; rows--; /* check margins */ ) {
		// use fast_memmove or fb_memmove
		*dest++ = *data++;
	}
}