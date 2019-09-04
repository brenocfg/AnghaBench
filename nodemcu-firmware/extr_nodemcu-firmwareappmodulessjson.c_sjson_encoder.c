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
struct TYPE_5__ {int nlevels; int level; void* null_ref; TYPE_1__* stack; void* current_str_ref; } ;
struct TYPE_4__ {void* lua_key_ref; void* lua_object_ref; } ;
typedef  TYPE_1__ ENC_DATA_STATE ;
typedef  TYPE_2__ ENC_DATA ;

/* Variables and functions */
 int DEFAULT_DEPTH ; 
 void* LUA_NOREF ; 
 void* LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  enc_push_stack (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 void* lua_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_encoder(lua_State *L) {
  int nlevels = DEFAULT_DEPTH;
  int argno = 1;

  // Validate first arg is a table
  luaL_checktype(L, argno++, LUA_TTABLE);

  if (lua_type(L, argno) == LUA_TTABLE) {
    lua_getfield(L, argno, "depth");
    nlevels = lua_tointeger(L, argno);
    if (nlevels == 0) {
      nlevels = DEFAULT_DEPTH;
    }
    if (nlevels < 4) {
      nlevels = 4;
    }
    if (nlevels > 1000) {
      nlevels = 1000;
    }
    lua_pop(L, 1);
  }

  ENC_DATA *data = (ENC_DATA *) lua_newuserdata(L, sizeof(ENC_DATA) + nlevels * sizeof(ENC_DATA_STATE));

  // Associate its metatable
  luaL_getmetatable(L, "sjson.encoder");
  lua_setmetatable(L, -2);

  data->nlevels = nlevels;
  data->level = -1;
  data->stack = (ENC_DATA_STATE *) (data + 1);
  data->current_str_ref = LUA_NOREF;
  int i;
  for (i = 0; i < nlevels; i++) {
    data->stack[i].lua_object_ref = LUA_NOREF;
    data->stack[i].lua_key_ref = LUA_REFNIL;
  }
  enc_push_stack(L, data, 1);

  data->null_ref = LUA_REFNIL;

  if (lua_type(L, argno) == LUA_TTABLE) {
    luaL_unref(L, LUA_REGISTRYINDEX, data->null_ref);
    data->null_ref = LUA_NOREF;
    lua_getfield(L, argno, "null");
    data->null_ref = lua_ref(L, 1);
  }

  return 1;
}