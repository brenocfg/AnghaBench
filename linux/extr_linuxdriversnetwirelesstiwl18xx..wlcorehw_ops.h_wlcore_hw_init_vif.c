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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* init_vif ) (struct wl1271*,struct wl12xx_vif*) ;} ;

/* Variables and functions */
 int stub1 (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static inline int
wlcore_hw_init_vif(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	if (wl->ops->init_vif)
		return wl->ops->init_vif(wl, wlvif);

	return 0;
}