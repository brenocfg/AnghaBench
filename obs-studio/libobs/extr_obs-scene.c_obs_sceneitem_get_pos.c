#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vec2 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  vec2_copy (struct vec2*,int /*<<< orphan*/ *) ; 

void obs_sceneitem_get_pos(const obs_sceneitem_t *item, struct vec2 *pos)
{
	if (item)
		vec2_copy(pos, &item->pos);
}