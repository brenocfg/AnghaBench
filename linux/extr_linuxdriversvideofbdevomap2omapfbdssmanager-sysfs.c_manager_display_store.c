#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay_manager {int (* apply ) (struct omap_overlay_manager*) ;struct omap_dss_device* (* get_device ) (struct omap_overlay_manager*) ;} ;
struct omap_dss_device {TYPE_1__* driver; int /*<<< orphan*/  name; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* connect ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* disconnect ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  manager_display_match ; 
 struct omap_dss_device* omap_dss_find_device (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_connected (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_enabled (struct omap_dss_device*) ; 
 struct omap_dss_device* stub1 (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 
 int stub3 (struct omap_dss_device*) ; 
 struct omap_dss_device* stub4 (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  stub5 (struct omap_dss_device*) ; 
 int stub6 (struct omap_overlay_manager*) ; 

__attribute__((used)) static ssize_t manager_display_store(struct omap_overlay_manager *mgr,
		const char *buf, size_t size)
{
	int r = 0;
	size_t len = size;
	struct omap_dss_device *dssdev = NULL;
	struct omap_dss_device *old_dssdev;

	if (buf[size-1] == '\n')
		--len;

	if (len > 0)
		dssdev = omap_dss_find_device((void *)buf,
			manager_display_match);

	if (len > 0 && dssdev == NULL)
		return -EINVAL;

	if (dssdev) {
		DSSDBG("display %s found\n", dssdev->name);

		if (omapdss_device_is_connected(dssdev)) {
			DSSERR("new display is already connected\n");
			r = -EINVAL;
			goto put_device;
		}

		if (omapdss_device_is_enabled(dssdev)) {
			DSSERR("new display is not disabled\n");
			r = -EINVAL;
			goto put_device;
		}
	}

	old_dssdev = mgr->get_device(mgr);
	if (old_dssdev) {
		if (omapdss_device_is_enabled(old_dssdev)) {
			DSSERR("old display is not disabled\n");
			r = -EINVAL;
			goto put_device;
		}

		old_dssdev->driver->disconnect(old_dssdev);
	}

	if (dssdev) {
		r = dssdev->driver->connect(dssdev);
		if (r) {
			DSSERR("failed to connect new device\n");
			goto put_device;
		}

		old_dssdev = mgr->get_device(mgr);
		if (old_dssdev != dssdev) {
			DSSERR("failed to connect device to this manager\n");
			dssdev->driver->disconnect(dssdev);
			goto put_device;
		}

		r = mgr->apply(mgr);
		if (r) {
			DSSERR("failed to apply dispc config\n");
			goto put_device;
		}
	}

put_device:
	if (dssdev)
		omap_dss_put_device(dssdev);

	return r ? r : size;
}