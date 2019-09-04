#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {size_t level; TYPE_1__* stack; } ;
struct TYPE_4__ {int /*<<< orphan*/  lua_key_ref; int /*<<< orphan*/  lua_object_ref; } ;
typedef  TYPE_1__ ENC_DATA_STATE ;
typedef  TYPE_2__ ENC_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REFNIL ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc_pop_stack(lua_State *L, ENC_DATA *data) {
  if (data->level < 0) {
    luaL_error(L, "encoder stack underflow");
  }
  ENC_DATA_STATE *state = &data->stack[data->level];

  lua_unref(L, state->lua_object_ref);
  state->lua_object_ref = LUA_NOREF;
  lua_unref(L, state->lua_key_ref);
  state->lua_key_ref = LUA_REFNIL;
  data->level--;
}