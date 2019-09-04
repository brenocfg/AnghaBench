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
struct tcx_par {scalar_t__ lowdepth; } ;
struct TYPE_2__ {int line_length; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_SUN_TCX ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
tcx_init_fix(struct fb_info *info, int linebytes)
{
	struct tcx_par *par = (struct tcx_par *)info->par;
	const char *tcx_name;

	if (par->lowdepth)
		tcx_name = "TCX8";
	else
		tcx_name = "TCX24";

	strlcpy(info->fix.id, tcx_name, sizeof(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_TCX;
}