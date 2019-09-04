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
struct xgifb_video_info {int mode_idx; } ;
struct TYPE_2__ {scalar_t__ mode_no; unsigned int xres; unsigned int yres; unsigned int bpp; } ;

/* Variables and functions */
 TYPE_1__* XGIbios_mode ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void XGIfb_search_mode(struct xgifb_video_info *xgifb_info,
			      const char *name)
{
	unsigned int xres;
	unsigned int yres;
	unsigned int bpp;
	int i;

	if (sscanf(name, "%ux%ux%u", &xres, &yres, &bpp) != 3)
		goto invalid_mode;

	if (bpp == 24)
		bpp = 32; /* That's for people who mix up color and fb depth. */

	for (i = 0; XGIbios_mode[i].mode_no != 0; i++)
		if (XGIbios_mode[i].xres == xres &&
		    XGIbios_mode[i].yres == yres &&
		    XGIbios_mode[i].bpp == bpp) {
			xgifb_info->mode_idx = i;
			return;
		}
invalid_mode:
	pr_info("Invalid mode '%s'\n", name);
}