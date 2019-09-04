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
struct omap_overlay_manager {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct omap_overlay_manager*) ;} ;

/* Variables and functions */
 TYPE_1__* dss_mgr_ops ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*) ; 

void dss_mgr_disable(struct omap_overlay_manager *mgr)
{
	dss_mgr_ops->disable(mgr);
}