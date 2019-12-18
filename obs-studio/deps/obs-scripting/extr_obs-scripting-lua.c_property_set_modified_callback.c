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
struct lua_obs_callback {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct lua_obs_callback* add_lua_obs_callback (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_function (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ls_get_libobs_obj (int,int,int*) ; 
 int /*<<< orphan*/  modified_callback ; 
 int /*<<< orphan*/  obs_property_set_modified_callback2 (int,int /*<<< orphan*/ ,struct lua_obs_callback*) ; 
 int obs_property_t ; 
 int p ; 

__attribute__((used)) static int property_set_modified_callback(lua_State *script)
{
	obs_property_t *p;

	if (!ls_get_libobs_obj(obs_property_t, 1, &p))
		return 0;
	if (!is_function(script, 2))
		return 0;

	struct lua_obs_callback *cb = add_lua_obs_callback(script, 2);
	obs_property_set_modified_callback2(p, modified_callback, cb);
	return 0;
}