#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  obs_scene_t ;
typedef  int /*<<< orphan*/  (* obs_scene_atomic_update_func ) (void*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  full_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_scene_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_scene_release (int /*<<< orphan*/ *) ; 

void obs_scene_atomic_update(obs_scene_t *scene,
			     obs_scene_atomic_update_func func, void *data)
{
	if (!scene)
		return;

	obs_scene_addref(scene);
	full_lock(scene);
	func(data, scene);
	full_unlock(scene);
	obs_scene_release(scene);
}