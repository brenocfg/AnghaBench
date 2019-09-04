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
struct platform_device {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _dsi_initialize_irq (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct platform_device*) ; 
 int dsi_display_init_dsi (struct platform_device*) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_runtime_get (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsi_display_enable(struct omap_dss_device *dssdev)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	int r = 0;

	DSSDBG("dsi_display_enable\n");

	WARN_ON(!dsi_bus_is_locked(dsidev));

	mutex_lock(&dsi->lock);

	r = dsi_runtime_get(dsidev);
	if (r)
		goto err_get_dsi;

	_dsi_initialize_irq(dsidev);

	r = dsi_display_init_dsi(dsidev);
	if (r)
		goto err_init_dsi;

	mutex_unlock(&dsi->lock);

	return 0;

err_init_dsi:
	dsi_runtime_put(dsidev);
err_get_dsi:
	mutex_unlock(&dsi->lock);
	DSSDBG("dsi_display_enable FAILED\n");
	return r;
}