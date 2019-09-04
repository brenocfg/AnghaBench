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
struct omap_overlay_manager {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void dss_manager_kobj_uninit(struct omap_overlay_manager *mgr)
{
	kobject_del(&mgr->kobj);
	kobject_put(&mgr->kobj);

	memset(&mgr->kobj, 0, sizeof(mgr->kobj));
}