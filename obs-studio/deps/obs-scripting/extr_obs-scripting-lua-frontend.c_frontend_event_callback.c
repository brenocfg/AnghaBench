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
typedef  enum obs_frontend_event { ____Placeholder_obs_frontend_event } obs_frontend_event ;

/* Variables and functions */
 int /*<<< orphan*/  call_func (void (*) (int,void*),int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_callback () ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obs_frontend_remove_event_callback (void (*) (int,void*),struct lua_obs_callback*) ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void frontend_event_callback(enum obs_frontend_event event, void *priv)
{
	struct lua_obs_callback *cb = priv;
	lua_State *script = cb->script;

	if (cb->base.removed) {
		obs_frontend_remove_event_callback(frontend_event_callback, cb);
		return;
	}

	lock_callback();

	lua_pushinteger(script, (int)event);
	call_func(frontend_event_callback, 1, 0);

	unlock_callback();
}