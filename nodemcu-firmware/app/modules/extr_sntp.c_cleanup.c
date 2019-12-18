#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  list_ref; int /*<<< orphan*/  err_cb_ref; int /*<<< orphan*/  sync_cb_ref; int /*<<< orphan*/  pcb; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup (lua_State *L)
{
  os_timer_disarm (&state->timer);
  udp_remove (state->pcb);
  luaL_unref (L, LUA_REGISTRYINDEX, state->sync_cb_ref);
  luaL_unref (L, LUA_REGISTRYINDEX, state->err_cb_ref);
  luaL_unref (L, LUA_REGISTRYINDEX, state->list_ref);
  free (state);
  state = 0;
}