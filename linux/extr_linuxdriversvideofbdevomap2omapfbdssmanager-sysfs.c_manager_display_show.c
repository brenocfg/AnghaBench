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
struct omap_overlay_manager {struct omap_dss_device* (* get_device ) (struct omap_overlay_manager*) ;} ;
struct omap_dss_device {char* name; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct omap_dss_device* stub1 (struct omap_overlay_manager*) ; 

__attribute__((used)) static ssize_t manager_display_show(struct omap_overlay_manager *mgr, char *buf)
{
	struct omap_dss_device *dssdev = mgr->get_device(mgr);

	return snprintf(buf, PAGE_SIZE, "%s\n", dssdev ?
			dssdev->name : "<none>");
}