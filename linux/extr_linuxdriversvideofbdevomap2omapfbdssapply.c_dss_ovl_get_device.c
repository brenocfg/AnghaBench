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
struct omap_overlay {scalar_t__ manager; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 struct omap_dss_device* dss_mgr_get_device (scalar_t__) ; 

__attribute__((used)) static struct omap_dss_device *dss_ovl_get_device(struct omap_overlay *ovl)
{
	return ovl->manager ? dss_mgr_get_device(ovl->manager) : NULL;
}