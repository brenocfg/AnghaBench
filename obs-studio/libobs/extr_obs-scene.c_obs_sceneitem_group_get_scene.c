#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* source; scalar_t__ is_group; } ;
typedef  TYPE_3__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_scene_t ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */

obs_scene_t *obs_sceneitem_group_get_scene(const obs_sceneitem_t *item)
{
	return (item && item->is_group) ? item->source->context.data : NULL;
}