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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  enum_items_proc ; 
 int /*<<< orphan*/  ls_get_libobs_obj (int,int,int*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_scene_enum_items (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int obs_scene_t ; 
 int scene ; 

__attribute__((used)) static int scene_enum_items(lua_State *script)
{
	obs_scene_t *scene;
	if (!ls_get_libobs_obj(obs_scene_t, 1, &scene))
		return 0;

	lua_newtable(script);
	obs_scene_enum_items(scene, enum_items_proc, script);
	return 1;
}