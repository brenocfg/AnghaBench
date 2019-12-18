#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ removed; } ;
struct lua_obs_callback {TYPE_1__ base; int /*<<< orphan*/ * script; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  call_func (void (*) (void*,scalar_t__,scalar_t__),int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_callback () ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_remove_main_render_callback (void (*) (void*,scalar_t__,scalar_t__),struct lua_obs_callback*) ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void obs_lua_main_render_callback(void *priv, uint32_t cx, uint32_t cy)
{
	struct lua_obs_callback *cb = priv;
	lua_State *script = cb->script;

	if (cb->base.removed) {
		obs_remove_main_render_callback(obs_lua_main_render_callback,
						cb);
		return;
	}

	lock_callback();

	lua_pushinteger(script, (lua_Integer)cx);
	lua_pushinteger(script, (lua_Integer)cy);
	call_func(obs_lua_main_render_callback, 2, 0);

	unlock_callback();
}