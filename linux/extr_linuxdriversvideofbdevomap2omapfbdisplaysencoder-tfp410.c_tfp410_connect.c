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
struct TYPE_4__ {TYPE_1__* dpi; } ;
struct omap_dss_device {struct omap_dss_device* dst; struct omap_dss_device* src; TYPE_2__ ops; } ;
struct TYPE_3__ {int (* connect ) (struct omap_dss_device*,struct omap_dss_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ omapdss_device_is_connected (struct omap_dss_device*) ; 
 int stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int tfp410_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;
	int r;

	if (omapdss_device_is_connected(dssdev))
		return -EBUSY;

	r = in->ops.dpi->connect(in, dssdev);
	if (r)
		return r;

	dst->src = dssdev;
	dssdev->dst = dst;

	return 0;
}