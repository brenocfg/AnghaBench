#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  lvl; } ;
typedef  TYPE_1__ luaL_Buffer ;
struct TYPE_14__ {size_t level; scalar_t__ offset; void* current_str_ref; TYPE_2__* stack; } ;
struct TYPE_13__ {scalar_t__ size; int offset; int lua_object_ref; int lua_key_ref; } ;
typedef  TYPE_2__ ENC_DATA_STATE ;
typedef  TYPE_3__ ENC_DATA ;

/* Variables and functions */
 int LUA_NOREF ; 
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  enc_pop_stack (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  enc_push_stack (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  encode_lua_object (int /*<<< orphan*/ *,TYPE_3__*,int,char*,char*) ; 
 int /*<<< orphan*/  luaL_addchar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  luaL_addvalue (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_pushresult (TYPE_1__*) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 void* lua_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_unref (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sjson_encoder_next_value_is_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sjson_encoder_make_next_chunk(lua_State *L, ENC_DATA *data) {
  if (data->level < 0) {
    return;
  }

  luaL_Buffer b;
  luaL_buffinit(L, &b);

  // Ending condition
  while (data->level >= 0 && !b.lvl) {
    ENC_DATA_STATE *state = &data->stack[data->level];

    int finished = 0;

    if (state->size >= 0) {
      if (state->offset == 0) {
        // start of object or whatever
        luaL_addchar(&b, '[');
      }
      if (state->offset == state->size << 1) {
        luaL_addchar(&b, ']');
        finished = 1;
      } else if ((state->offset & 1) == 0) {
        if (state->offset > 0) {
          luaL_addchar(&b, ',');
        }
      } else {
        // output the value
        lua_rawgeti(L, LUA_REGISTRYINDEX, state->lua_object_ref);
        lua_rawgeti(L, -1, (state->offset >> 1) + 1);
        if (sjson_encoder_next_value_is_table(L)) {
          enc_push_stack(L, data, -1);
          lua_pop(L, 2);
          state->offset++;
          continue;
        }
        encode_lua_object(L, data, -1, "", "");
        lua_remove(L, -2);
        lua_remove(L, -2);
        luaL_addvalue(&b);
      }

      state->offset++;
    } else {
      lua_rawgeti(L, LUA_REGISTRYINDEX, state->lua_object_ref);
      // stack now contains: -1 => table
      lua_rawgeti(L, LUA_REGISTRYINDEX, state->lua_key_ref);
      // stack now contains: -1 => nil or key; -2 => table

      if (lua_next(L, -2)) {
        // save the key
        if (state->offset & 1) {
          lua_unref(L, state->lua_key_ref);
          state->lua_key_ref = LUA_NOREF;
          // Duplicate the key
          lua_pushvalue(L, -2);
          state->lua_key_ref = lua_ref(L, 1);
        }

        if ((state->offset & 1) == 0) {
          // copy the key so that lua_tostring does not modify the original
          lua_pushvalue(L, -2);
          // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
          // key
          lua_tostring(L, -1);
          encode_lua_object(L, data, -1, state->offset ? "," : "{", ":");
          lua_remove(L, -2);
          lua_remove(L, -2);
          lua_remove(L, -2);
          lua_remove(L, -2);
        } else {
          if (sjson_encoder_next_value_is_table(L)) {
            enc_push_stack(L, data, -1);
            lua_pop(L, 3);
            state->offset++;
            continue;
          }
          encode_lua_object(L, data, -1, "", "");
          lua_remove(L, -2);
          lua_remove(L, -2);
          lua_remove(L, -2);
        }
        luaL_addvalue(&b);
      } else {
        lua_pop(L, 1);
        // We have got to the end
        luaL_addchar(&b, '}');
        finished = 1;
      }

      state->offset++;
    }

    if (finished) {
      enc_pop_stack(L, data);
    }
  }
  luaL_pushresult(&b);
  data->current_str_ref = lua_ref(L, 1);
  data->offset = 0;
}