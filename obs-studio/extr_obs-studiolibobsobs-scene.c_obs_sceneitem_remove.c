#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int removed; TYPE_2__* parent; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
struct TYPE_11__ {int /*<<< orphan*/ * source; } ;
typedef  TYPE_2__ obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_sceneitem (TYPE_1__*) ; 
 int /*<<< orphan*/  full_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_sceneitem_release (TYPE_1__*) ; 
 int /*<<< orphan*/  set_visibility (TYPE_1__*,int) ; 
 int /*<<< orphan*/  signal_item_remove (TYPE_1__*) ; 

void obs_sceneitem_remove(obs_sceneitem_t *item)
{
	obs_scene_t *scene;

	if (!item)
		return;

	scene = item->parent;

	full_lock(scene);

	if (item->removed) {
		if (scene)
			full_unlock(scene);
		return;
	}

	item->removed = true;

	assert(scene != NULL);
	assert(scene->source != NULL);

	set_visibility(item, false);

	signal_item_remove(item);
	detach_sceneitem(item);

	full_unlock(scene);

	obs_sceneitem_release(item);
}