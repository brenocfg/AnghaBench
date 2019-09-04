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
struct radeonfb_info {int dummy; } ;

/* Variables and functions */

void radeonfb_pm_exit(struct radeonfb_info *rinfo)
{
#if defined(CONFIG_PM) && defined(CONFIG_PPC_PMAC)
	if (rinfo->pm_mode != radeon_pm_none)
		pmac_set_early_video_resume(NULL, NULL);
#endif
}