#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {int length; } ;
struct TYPE_4__ {int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */

__attribute__((used)) static inline int pm3fb_depth(const struct fb_var_screeninfo *var)
{
	if (var->bits_per_pixel == 16)
		return var->red.length + var->green.length
			+ var->blue.length;

	return var->bits_per_pixel;
}