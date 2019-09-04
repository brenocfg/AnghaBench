#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panel_drv_data {struct omap_dss_device* in; } ;
struct omap_video_timings {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dpi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_3__ {int (* check_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;} ;

/* Variables and functions */
 int stub1 (struct omap_dss_device*,struct omap_video_timings*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int nec_8048_check_timings(struct omap_dss_device *dssdev,
		struct omap_video_timings *timings)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;

	return in->ops.dpi->check_timings(in, timings);
}