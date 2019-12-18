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
struct TYPE_4__ {int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_update_transform (TYPE_1__*) ; 
 int /*<<< orphan*/  vec2_copy (int /*<<< orphan*/ *,struct vec2 const*) ; 

void obs_sceneitem_set_scale(obs_sceneitem_t *item, const struct vec2 *scale)
{
	if (item) {
		vec2_copy(&item->scale, scale);
		do_update_transform(item);
	}
}