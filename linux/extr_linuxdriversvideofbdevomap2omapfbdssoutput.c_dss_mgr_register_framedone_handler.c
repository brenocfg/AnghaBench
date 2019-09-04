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
struct TYPE_2__ {int (* register_framedone_handler ) (struct omap_overlay_manager*,void (*) (void*),void*) ;} ;

/* Variables and functions */
 TYPE_1__* dss_mgr_ops ; 
 int stub1 (struct omap_overlay_manager*,void (*) (void*),void*) ; 

int dss_mgr_register_framedone_handler(struct omap_overlay_manager *mgr,
		void (*handler)(void *), void *data)
{
	return dss_mgr_ops->register_framedone_handler(mgr, handler, data);
}