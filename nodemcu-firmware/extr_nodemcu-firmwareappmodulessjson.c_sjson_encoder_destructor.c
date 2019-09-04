#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int nlevels; int /*<<< orphan*/  current_str_ref; int /*<<< orphan*/  null_ref; TYPE_1__* stack; } ;
struct TYPE_3__ {int /*<<< orphan*/  lua_key_ref; int /*<<< orphan*/  lua_object_ref; } ;
typedef  TYPE_2__ ENC_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINTF (char*) ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sjson_encoder_destructor(lua_State *L) {
  ENC_DATA *data = (ENC_DATA *)luaL_checkudata(L, 1, "sjson.encoder");

  int i;

  for (i = 0; i < data->nlevels; i++) {
    luaL_unref(L, LUA_REGISTRYINDEX, data->stack[i].lua_object_ref);
    luaL_unref(L, LUA_REGISTRYINDEX, data->stack[i].lua_key_ref);
  }

  luaL_unref(L, LUA_REGISTRYINDEX, data->null_ref);
  luaL_unref(L, LUA_REGISTRYINDEX, data->current_str_ref);

  DBG_PRINTF("Destructor called\n");

  return 0;
}