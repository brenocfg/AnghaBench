#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* source; int /*<<< orphan*/  is_group; } ;
typedef  TYPE_3__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_scene_t ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_scene_enum_items (int /*<<< orphan*/ *,int (*) (obs_scene_t*,TYPE_3__*,void*),void*) ; 

void obs_sceneitem_group_enum_items(obs_sceneitem_t *group,
				    bool (*callback)(obs_scene_t *,
						     obs_sceneitem_t *, void *),
				    void *param)
{
	if (!group || !group->is_group)
		return;

	obs_scene_t *scene = group->source->context.data;
	if (scene)
		obs_scene_enum_items(scene, callback, param);
}