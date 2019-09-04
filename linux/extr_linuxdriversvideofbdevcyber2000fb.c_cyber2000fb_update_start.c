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
typedef  int u_int ;
struct fb_var_screeninfo {int yoffset; int xres_virtual; int xoffset; int bits_per_pixel; } ;
struct cfb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cyber2000_crtcw (int,int,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000_grphw (int,int,struct cfb_info*) ; 

__attribute__((used)) static inline int
cyber2000fb_update_start(struct cfb_info *cfb, struct fb_var_screeninfo *var)
{
	u_int base = var->yoffset * var->xres_virtual + var->xoffset;

	base *= var->bits_per_pixel;

	/*
	 * Convert to bytes and shift two extra bits because DAC
	 * can only start on 4 byte aligned data.
	 */
	base >>= 5;

	if (base >= 1 << 20)
		return -EINVAL;

	cyber2000_grphw(0x10, base >> 16 | 0x10, cfb);
	cyber2000_crtcw(0x0c, base >> 8, cfb);
	cyber2000_crtcw(0x0d, base, cfb);

	return 0;
}