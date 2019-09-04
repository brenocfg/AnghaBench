#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  TYPE_2__* jsonsl_t ;
struct TYPE_9__ {TYPE_2__* jsn; void* pos_ref; void* metatable; void* null_ref; void* result_ref; int /*<<< orphan*/  min_available; int /*<<< orphan*/  min_needed; scalar_t__ buffer_len; int /*<<< orphan*/ * L; int /*<<< orphan*/ * error; scalar_t__ complete; void* buffer_ref; void* hkey_ref; } ;
struct TYPE_8__ {int levels_max; int max_callback_level; TYPE_3__* data; int /*<<< orphan*/  error_callback; int /*<<< orphan*/  action_callback_POP; int /*<<< orphan*/  action_callback_PUSH; int /*<<< orphan*/ * action_callback; int /*<<< orphan*/  pos; TYPE_1__* stack; } ;
struct TYPE_7__ {void* lua_object_ref; } ;
typedef  TYPE_3__ JSN_DATA ;

/* Variables and functions */
 int DEFAULT_DEPTH ; 
 void* LUA_NOREF ; 
 void* LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TNIL ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  cleanup_closing_element ; 
 int /*<<< orphan*/  create_new_element ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  jsonsl_enable_all_callbacks (TYPE_2__*) ; 
 scalar_t__ jsonsl_get_size (int) ; 
 TYPE_2__* jsonsl_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 void* lua_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_decoder_int(lua_State *L, int argno) {
  int nlevels = DEFAULT_DEPTH;

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

  JSN_DATA *data = (JSN_DATA *) lua_newuserdata(L, sizeof(JSN_DATA) + jsonsl_get_size(nlevels));
  //
  // Associate its metatable
  luaL_getmetatable(L, "sjson.decoder");
  lua_setmetatable(L, -2);

  jsonsl_t jsn = jsonsl_init((jsonsl_t) (data + 1), nlevels);
  int i;

  for (i = 0; i < jsn->levels_max; i++) {
    jsn->stack[i].lua_object_ref = LUA_NOREF;
  }
  data->jsn = jsn;
  data->result_ref = LUA_NOREF;

  data->null_ref = LUA_REFNIL;
  data->metatable = LUA_NOREF;
  data->hkey_ref = LUA_NOREF;
  data->pos_ref = LUA_NOREF;
  data->buffer_ref = LUA_NOREF;
  data->complete = 0;
  data->error = NULL;
  data->L = L;
  data->buffer_len = 0;

  data->min_needed = data->min_available = jsn->pos;

  lua_pushlightuserdata(L, 0);
  data->null_ref = lua_ref(L, 1);

  // This may throw...
  lua_newtable(L);
  data->result_ref = luaL_ref(L, LUA_REGISTRYINDEX);

  if (lua_type(L, argno) == LUA_TTABLE) {
    luaL_unref(L, LUA_REGISTRYINDEX, data->null_ref);
    data->null_ref = LUA_NOREF;
    lua_getfield(L, argno, "null");
    data->null_ref = lua_ref(L, 1);

    lua_getfield(L, argno, "metatable");
    lua_pushvalue(L, -1);
    data->metatable = lua_ref(L, 1);

    if (lua_type(L, -1) != LUA_TNIL) {
      lua_getfield(L, -1, "checkpath");
      if (lua_type(L, -1) != LUA_TNIL) {
        lua_newtable(L);
        data->pos_ref = lua_ref(L, 1);
      }
      lua_pop(L, 1);      // Throw away the checkpath value
    }
    lua_pop(L, 1);      // Throw away the metatable
  }

  jsonsl_enable_all_callbacks(data->jsn);

  jsn->action_callback = NULL;
  jsn->action_callback_PUSH = create_new_element;
  jsn->action_callback_POP = cleanup_closing_element;
  jsn->error_callback = error_callback;
  jsn->data = data;
  jsn->max_callback_level = nlevels;

  return 1;
}