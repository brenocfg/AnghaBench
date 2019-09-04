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
struct fb_var_screeninfo {int grayscale; } ;

/* Variables and functions */

__attribute__((used)) static int sh_mobile_format_is_fourcc(const struct fb_var_screeninfo *var)
{
	return var->grayscale > 1;
}