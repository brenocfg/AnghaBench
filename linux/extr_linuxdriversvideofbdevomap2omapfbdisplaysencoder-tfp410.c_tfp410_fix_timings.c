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
struct omap_video_timings {int /*<<< orphan*/  de_level; void* sync_pclk_edge; void* data_pclk_edge; } ;

/* Variables and functions */
 void* OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 int /*<<< orphan*/  OMAPDSS_SIG_ACTIVE_HIGH ; 

__attribute__((used)) static void tfp410_fix_timings(struct omap_video_timings *timings)
{
	timings->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	timings->sync_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	timings->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
}