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
struct omap_video_timings {int dummy; } ;
struct omap_dss_device {int /*<<< orphan*/  dispc_channel; } ;
struct TYPE_2__ {struct omap_dss_device output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dispc_mgr_timings_ok (int /*<<< orphan*/ ,struct omap_video_timings*) ; 
 TYPE_1__ hdmi ; 

__attribute__((used)) static int hdmi_display_check_timing(struct omap_dss_device *dssdev,
					struct omap_video_timings *timings)
{
	struct omap_dss_device *out = &hdmi.output;

	if (!dispc_mgr_timings_ok(out->dispc_channel, timings))
		return -EINVAL;

	return 0;
}