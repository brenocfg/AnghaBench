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
struct omap_dss_device {scalar_t__ manager; struct omap_dss_device* dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (scalar_t__,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_output_unset_device (struct omap_dss_device*) ; 

__attribute__((used)) static void hdmi_disconnect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	WARN_ON(dst != dssdev->dst);

	if (dst != dssdev->dst)
		return;

	omapdss_output_unset_device(dssdev);

	if (dssdev->manager)
		dss_mgr_disconnect(dssdev->manager, dssdev);
}