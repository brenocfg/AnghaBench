#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_scene_item {struct obs_scene_item* next; TYPE_2__* source; } ;
typedef  struct obs_scene_item obs_sceneitem_t ;
struct TYPE_9__ {struct obs_scene_item* first_item; } ;
typedef  TYPE_3__ obs_scene_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_3__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

obs_sceneitem_t *obs_scene_find_source(obs_scene_t *scene, const char *name)
{
	struct obs_scene_item *item;

	if (!scene)
		return NULL;

	full_lock(scene);

	item = scene->first_item;
	while (item) {
		if (strcmp(item->source->context.name, name) == 0)
			break;

		item = item->next;
	}

	full_unlock(scene);

	return item;
}