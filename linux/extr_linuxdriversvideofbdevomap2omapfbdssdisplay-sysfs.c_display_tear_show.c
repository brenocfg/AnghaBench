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
struct TYPE_2__ {int (* get_te ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct omap_dss_device*) ; 
 int stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static ssize_t display_tear_show(struct omap_dss_device *dssdev, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n",
			dssdev->driver->get_te ?
			dssdev->driver->get_te(dssdev) : 0);
}