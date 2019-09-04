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
struct nvidia_par {int /*<<< orphan*/  lockup; } ;
struct fb_info {scalar_t__ state; struct nvidia_par* par; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  NVFlush (struct fb_info*) ; 
 int /*<<< orphan*/  NVSync (struct fb_info*) ; 

int nvidiafb_sync(struct fb_info *info)
{
	struct nvidia_par *par = info->par;

	if (info->state != FBINFO_STATE_RUNNING)
		return 0;

	if (!par->lockup)
		NVFlush(info);

	if (!par->lockup)
		NVSync(info);

	return 0;
}