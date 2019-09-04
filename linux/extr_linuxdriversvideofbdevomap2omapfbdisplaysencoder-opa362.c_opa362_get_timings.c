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
struct omap_video_timings {int dummy; } ;
struct panel_drv_data {struct omap_video_timings timings; } ;
struct omap_dss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void opa362_get_timings(struct omap_dss_device *dssdev,
		struct omap_video_timings *timings)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);

	dev_dbg(dssdev->dev, "get_timings\n");

	*timings = ddata->timings;
}