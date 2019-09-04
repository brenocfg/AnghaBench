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
struct TYPE_2__ {int (* enable_te ) (struct omap_dss_device*,int) ;int /*<<< orphan*/  get_te; } ;

/* Variables and functions */
 int ENOENT ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct omap_dss_device*,int) ; 

__attribute__((used)) static ssize_t display_tear_store(struct omap_dss_device *dssdev,
	const char *buf, size_t size)
{
	int r;
	bool te;

	if (!dssdev->driver->enable_te || !dssdev->driver->get_te)
		return -ENOENT;

	r = strtobool(buf, &te);
	if (r)
		return r;

	r = dssdev->driver->enable_te(dssdev, te);
	if (r)
		return r;

	return size;
}