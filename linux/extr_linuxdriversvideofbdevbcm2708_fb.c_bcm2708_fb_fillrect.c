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
struct fb_info {int dummy; } ;
struct fb_fillrect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void bcm2708_fb_fillrect(struct fb_info *info,
				const struct fb_fillrect *rect)
{
	/* (is called) print_debug("bcm2708_fb_fillrect\n"); */
	cfb_fillrect(info, rect);
}