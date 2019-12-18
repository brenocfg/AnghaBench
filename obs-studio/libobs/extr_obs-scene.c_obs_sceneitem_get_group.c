#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ is_group; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  full_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_sceneitem_parent_group (int /*<<< orphan*/ *,TYPE_1__*) ; 

obs_sceneitem_t *obs_sceneitem_get_group(obs_scene_t *scene,
					 obs_sceneitem_t *group_subitem)
{
	if (!scene || !group_subitem || group_subitem->is_group)
		return NULL;

	full_lock(scene);
	obs_sceneitem_t *group =
		get_sceneitem_parent_group(scene, group_subitem);
	full_unlock(scene);

	return group;
}