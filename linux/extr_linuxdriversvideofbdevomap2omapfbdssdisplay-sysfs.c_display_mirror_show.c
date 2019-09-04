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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int (* get_mirror ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct omap_dss_device*) ; 

__attribute__((used)) static ssize_t display_mirror_show(struct omap_dss_device *dssdev, char *buf)
{
	int mirror;
	if (!dssdev->driver->get_mirror)
		return -ENOENT;
	mirror = dssdev->driver->get_mirror(dssdev);
	return snprintf(buf, PAGE_SIZE, "%u\n", mirror);
}