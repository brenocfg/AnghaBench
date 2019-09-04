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
struct omap_dss_device {TYPE_1__* driver; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* enable ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int omapdss_device_is_connected (struct omap_dss_device*) ; 
 int omapdss_device_is_enabled (struct omap_dss_device*) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static ssize_t display_enabled_store(struct omap_dss_device *dssdev,
		const char *buf, size_t size)
{
	int r;
	bool enable;

	r = strtobool(buf, &enable);
	if (r)
		return r;

	if (enable == omapdss_device_is_enabled(dssdev))
		return size;

	if (omapdss_device_is_connected(dssdev) == false)
		return -ENODEV;

	if (enable) {
		r = dssdev->driver->enable(dssdev);
		if (r)
			return r;
	} else {
		dssdev->driver->disable(dssdev);
	}

	return size;
}