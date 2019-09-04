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
struct radeonfb_info {scalar_t__ asleep; } ;
struct fb_info {struct radeonfb_info* par; } ;

/* Variables and functions */
 int radeon_screen_blank (struct radeonfb_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeonfb_blank (int blank, struct fb_info *info)
{
        struct radeonfb_info *rinfo = info->par;

	if (rinfo->asleep)
		return 0;
		
	return radeon_screen_blank(rinfo, blank, 0);
}