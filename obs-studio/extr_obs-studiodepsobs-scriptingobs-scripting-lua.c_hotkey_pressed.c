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

/* Variables and functions */
 int /*<<< orphan*/  call_func (void (*) (void*,int),int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_callback () ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void hotkey_pressed(void *p_cb, bool pressed)
{
	struct lua_obs_callback *cb = p_cb;
	lua_State *script = cb->script;

	if (cb->base.removed)
		return;

	lock_callback();

	lua_pushboolean(script, pressed);
	call_func(hotkey_pressed, 1, 0);

	unlock_callback();
}