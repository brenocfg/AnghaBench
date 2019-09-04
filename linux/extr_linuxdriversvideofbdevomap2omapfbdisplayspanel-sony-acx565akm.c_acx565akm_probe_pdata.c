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
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct panel_drv_data {struct omap_dss_device dssdev; int /*<<< orphan*/  datapairs; struct omap_dss_device* in; int /*<<< orphan*/  reset_gpio; } ;
struct panel_acx565akm_platform_data {int /*<<< orphan*/  name; int /*<<< orphan*/  datapairs; int /*<<< orphan*/  source; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct panel_acx565akm_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct omap_dss_device* omap_dss_find_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acx565akm_probe_pdata(struct spi_device *spi)
{
	const struct panel_acx565akm_platform_data *pdata;
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct omap_dss_device *dssdev, *in;

	pdata = dev_get_platdata(&spi->dev);

	ddata->reset_gpio = pdata->reset_gpio;

	in = omap_dss_find_output(pdata->source);
	if (in == NULL) {
		dev_err(&spi->dev, "failed to find video source '%s'\n",
				pdata->source);
		return -EPROBE_DEFER;
	}
	ddata->in = in;

	ddata->datapairs = pdata->datapairs;

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	return 0;
}