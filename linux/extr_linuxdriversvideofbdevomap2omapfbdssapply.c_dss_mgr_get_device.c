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
struct omap_overlay_manager {struct omap_dss_device* output; } ;
struct omap_dss_device {scalar_t__ driver; struct omap_dss_device* dst; } ;

/* Variables and functions */

__attribute__((used)) static struct omap_dss_device *dss_mgr_get_device(struct omap_overlay_manager *mgr)
{
	struct omap_dss_device *dssdev;

	dssdev = mgr->output;
	if (dssdev == NULL)
		return NULL;

	while (dssdev->dst)
		dssdev = dssdev->dst;

	if (dssdev->driver)
		return dssdev;
	else
		return NULL;
}