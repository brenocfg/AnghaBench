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
struct fb_info {int flags; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  viafb_wait_engine_idle (struct fb_info*) ; 

__attribute__((used)) static int viafb_sync(struct fb_info *info)
{
	if (!(info->flags & FBINFO_HWACCEL_DISABLED))
		viafb_wait_engine_idle(info);
	return 0;
}