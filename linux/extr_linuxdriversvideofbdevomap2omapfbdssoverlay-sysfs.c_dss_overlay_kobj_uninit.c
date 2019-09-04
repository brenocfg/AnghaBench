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
struct omap_overlay {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

void dss_overlay_kobj_uninit(struct omap_overlay *ovl)
{
	kobject_del(&ovl->kobj);
	kobject_put(&ovl->kobj);
}