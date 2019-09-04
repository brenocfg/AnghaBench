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
typedef  scalar_t__ u32 ;
struct nvidia_par {int dummy; } ;
struct fb_var_screeninfo {int yoffset; scalar_t__ xoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVSetStartAddress (struct nvidia_par*,scalar_t__) ; 

__attribute__((used)) static int nvidiafb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct nvidia_par *par = info->par;
	u32 total;

	total = var->yoffset * info->fix.line_length + var->xoffset;

	NVSetStartAddress(par, total);

	return 0;
}