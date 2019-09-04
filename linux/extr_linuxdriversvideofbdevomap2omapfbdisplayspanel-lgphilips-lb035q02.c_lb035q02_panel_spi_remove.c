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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct omap_dss_device {int dummy; } ;
struct panel_drv_data {struct omap_dss_device* in; struct omap_dss_device dssdev; } ;

/* Variables and functions */
 struct panel_drv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lb035q02_disable (struct omap_dss_device*) ; 
 int /*<<< orphan*/  lb035q02_disconnect (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_unregister_display (struct omap_dss_device*) ; 

__attribute__((used)) static int lb035q02_panel_spi_remove(struct spi_device *spi)
{
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct omap_dss_device *dssdev = &ddata->dssdev;
	struct omap_dss_device *in = ddata->in;

	omapdss_unregister_display(dssdev);

	lb035q02_disable(dssdev);
	lb035q02_disconnect(dssdev);

	omap_dss_put_device(in);

	return 0;
}