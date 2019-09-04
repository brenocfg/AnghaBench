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
struct hecubafb_par {int dummy; } ;
struct fb_info {struct hecubafb_par* par; } ;
struct fb_fillrect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hecubafb_dpy_update (struct hecubafb_par*) ; 
 int /*<<< orphan*/  sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void hecubafb_fillrect(struct fb_info *info,
				   const struct fb_fillrect *rect)
{
	struct hecubafb_par *par = info->par;

	sys_fillrect(info, rect);

	hecubafb_dpy_update(par);
}