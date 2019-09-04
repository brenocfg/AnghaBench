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
struct panel_drv_data {scalar_t__ enable_gpio; int /*<<< orphan*/  timings; struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* atv; } ;
struct omap_dss_device {int /*<<< orphan*/  state; TYPE_2__ ops; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* enable ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* set_timings ) (struct omap_dss_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_ACTIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  omapdss_device_is_connected (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_enabled (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int /*<<< orphan*/ *) ; 
 int stub2 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int opa362_enable(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;
	int r;

	dev_dbg(dssdev->dev, "enable\n");

	if (!omapdss_device_is_connected(dssdev))
		return -ENODEV;

	if (omapdss_device_is_enabled(dssdev))
		return 0;

	in->ops.atv->set_timings(in, &ddata->timings);

	r = in->ops.atv->enable(in);
	if (r)
		return r;

	if (ddata->enable_gpio)
		gpiod_set_value_cansleep(ddata->enable_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	return 0;
}