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
struct sis_video_info {scalar_t__ sisvga_engine; } ;

/* Variables and functions */
 scalar_t__ SIS_300_VGA ; 

void sisfb_syncaccel(struct sis_video_info *ivideo)
{
	if(ivideo->sisvga_engine == SIS_300_VGA) {
#ifdef CONFIG_FB_SIS_300
		SiS300Sync(ivideo);
#endif
	} else {
#ifdef CONFIG_FB_SIS_315
		SiS310Sync(ivideo);
#endif
	}
}