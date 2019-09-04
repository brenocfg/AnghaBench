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
 int /*<<< orphan*/  dsi_bus_is_locked (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_display_uninit_dsi (struct platform_device*,int,int) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_sync_vc (struct platform_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_display_disable(struct omap_dss_device *dssdev,
		bool disconnect_lanes, bool enter_ulps)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	DSSDBG("dsi_display_disable\n");

	WARN_ON(!dsi_bus_is_locked(dsidev));

	mutex_lock(&dsi->lock);

	dsi_sync_vc(dsidev, 0);
	dsi_sync_vc(dsidev, 1);
	dsi_sync_vc(dsidev, 2);
	dsi_sync_vc(dsidev, 3);

	dsi_display_uninit_dsi(dsidev, disconnect_lanes, enter_ulps);

	dsi_runtime_put(dsidev);

	mutex_unlock(&dsi->lock);
}