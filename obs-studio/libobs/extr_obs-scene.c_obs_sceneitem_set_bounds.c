#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vec2 {int dummy; } ;
struct TYPE_4__ {struct vec2 bounds; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_update_transform (TYPE_1__*) ; 

void obs_sceneitem_set_bounds(obs_sceneitem_t *item, const struct vec2 *bounds)
{
	if (item) {
		item->bounds = *bounds;
		do_update_transform(item);
	}
}