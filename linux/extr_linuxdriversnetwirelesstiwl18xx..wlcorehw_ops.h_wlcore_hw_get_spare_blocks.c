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
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_spare_blocks ) (struct wl1271*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (struct wl1271*,int) ; 

__attribute__((used)) static inline int
wlcore_hw_get_spare_blocks(struct wl1271 *wl, bool is_gem)
{
	if (!wl->ops->get_spare_blocks)
		BUG_ON(1);

	return wl->ops->get_spare_blocks(wl, is_gem);
}