#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int entry_count; int cb_ref; int stop_pos; } ;
typedef  TYPE_1__ pulse_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int32_t ;

/* Variables and functions */
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 scalar_t__ LUA_TNUMBER ; 
 TYPE_1__* active_pulser ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gpio_pulse_stop(lua_State *L) {
  pulse_t *pulser = luaL_checkudata(L, 1, "gpio.pulse");

  if (pulser != active_pulser) {
    return 0;
  }

  int argno = 2;

  int32_t stop_pos = -2;

  if (lua_type(L, argno) == LUA_TNUMBER) {
    stop_pos = luaL_checkinteger(L, 2);
    if (stop_pos != -2) {
      if (stop_pos < 1 || stop_pos > pulser->entry_count) {
        return luaL_error( L, "bad stop position: %d (valid range 1 - %d)", stop_pos, pulser->entry_count );
      }
      stop_pos = stop_pos - 1;
    }
    argno++;
  }

  if (lua_type(L, argno) == LUA_TFUNCTION || lua_type(L, argno) == LUA_TLIGHTFUNCTION) {
    lua_pushvalue(L, argno);
  } else {
    return luaL_error( L, "missing callback" );
  }

  int new_cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  int cb_ref = pulser->cb_ref;

  pulser->cb_ref = LUA_NOREF;
  pulser->stop_pos = -1;
  pulser->cb_ref = new_cb_ref;
  pulser->stop_pos = stop_pos;

  luaL_unref(L, LUA_REGISTRYINDEX, cb_ref);

  lua_pushboolean(L, 1);
  return 1;
}