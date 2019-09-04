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
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dispc_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int dss_mgr_connect (struct omap_overlay_manager*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (struct omap_overlay_manager*,struct omap_dss_device*) ; 
 struct omap_overlay_manager* omap_dss_get_overlay_manager (int /*<<< orphan*/ ) ; 
 int omapdss_output_set_device (struct omap_dss_device*,struct omap_dss_device*) ; 
 int venc_init_regulator () ; 

__attribute__((used)) static int venc_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct omap_overlay_manager *mgr;
	int r;

	r = venc_init_regulator();
	if (r)
		return r;

	mgr = omap_dss_get_overlay_manager(dssdev->dispc_channel);
	if (!mgr)
		return -ENODEV;

	r = dss_mgr_connect(mgr, dssdev);
	if (r)
		return r;

	r = omapdss_output_set_device(dssdev, dst);
	if (r) {
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(mgr, dssdev);
		return r;
	}

	return 0;
}