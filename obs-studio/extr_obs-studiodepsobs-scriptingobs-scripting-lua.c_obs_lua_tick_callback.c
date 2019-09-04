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
struct TYPE_2__ {scalar_t__ removed; } ;
struct lua_obs_callback {TYPE_1__ base; int /*<<< orphan*/ * script; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  call_func (void (*) (void*,float),int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_callback () ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_remove_tick_callback (void (*) (void*,float),struct lua_obs_callback*) ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void obs_lua_tick_callback(void *priv, float seconds)
{
	struct lua_obs_callback *cb = priv;
	lua_State *script = cb->script;

	if (cb->base.removed) {
		obs_remove_tick_callback(obs_lua_tick_callback, cb);
		return;
	}

	lock_callback();

	lua_pushnumber(script, (lua_Number)seconds);
	call_func(obs_lua_tick_callback, 1, 0);

	unlock_callback();
}