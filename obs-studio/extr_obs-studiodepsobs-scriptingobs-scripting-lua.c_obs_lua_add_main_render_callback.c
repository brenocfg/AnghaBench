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
 int /*<<< orphan*/  defer_add_render ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,struct lua_obs_callback*) ; 
 int /*<<< orphan*/  is_function ; 
 int /*<<< orphan*/  verify_args1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int obs_lua_add_main_render_callback(lua_State *script)
{
	if (!verify_args1(script, is_function))
		return 0;

	struct lua_obs_callback *cb = add_lua_obs_callback(script, 1);
	defer_call_post(defer_add_render, cb);
	return 0;
}