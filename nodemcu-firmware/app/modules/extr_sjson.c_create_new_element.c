#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jsonsl_state_st {int level; int type; void* lua_object_ref; int /*<<< orphan*/  pos_begin; int /*<<< orphan*/  used_count; } ;
typedef  TYPE_1__* jsonsl_t ;
typedef  int /*<<< orphan*/  jsonsl_action_t ;
struct TYPE_7__ {void* hkey_ref; void* pos_ref; void* metatable; int /*<<< orphan*/  min_needed; int /*<<< orphan*/  L; } ;
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_2__ JSN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINTF (char*,...) ; 
#define  JSONSL_T_HKEY 132 
#define  JSONSL_T_LIST 131 
#define  JSONSL_T_OBJECT 130 
#define  JSONSL_T_SPECIAL 129 
#define  JSONSL_T_STRING 128 
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TNIL ; 
 int /*<<< orphan*/  create_table (TYPE_2__*) ; 
 void* get_parent_object_ref () ; 
 int /*<<< orphan*/  get_parent_object_used_count_pre_inc () ; 
 int /*<<< orphan*/  get_state_buffer (TYPE_2__*,struct jsonsl_state_st*) ; 
 int /*<<< orphan*/  jsonsl_strtype (int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* lua_ref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ ,int) ; 
 int lua_toboolean (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_unref (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
create_new_element(jsonsl_t jsn,
                   jsonsl_action_t action,
                   struct jsonsl_state_st *state,
                   const char *buf)
{
  JSN_DATA *data = jsn->data;

  DBG_PRINTF("L%d: new action %d @ %d state->type %s\n", state->level, action, state->pos_begin, jsonsl_strtype(state->type));
  DBG_PRINTF("buf: '%s' ('%.10s')\n", buf, get_state_buffer(data, state));

  state->lua_object_ref = LUA_NOREF;

  switch(state->type) {
    case JSONSL_T_SPECIAL:
    case JSONSL_T_STRING:
    case JSONSL_T_HKEY:
      break;

    case JSONSL_T_LIST:
    case JSONSL_T_OBJECT:
      create_table(data);
      state->lua_object_ref = lua_ref(data->L, 1);
      state->used_count = 0;

      lua_rawgeti(data->L, LUA_REGISTRYINDEX, get_parent_object_ref());
      if (data->hkey_ref == LUA_NOREF) {
        // list, so append
        lua_pushnumber(data->L, get_parent_object_used_count_pre_inc());
        DBG_PRINTF("Adding array element\n");
      } else {
        // object, so
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->hkey_ref);
        lua_unref(data->L, data->hkey_ref);
        data->hkey_ref = LUA_NOREF;
        DBG_PRINTF("Adding hash element\n");
      }
      if (data->pos_ref != LUA_NOREF && state->level > 1) {
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->pos_ref);
        lua_pushnumber(data->L, state->level - 1);
        lua_pushvalue(data->L, -3);     // get the key
        lua_settable(data->L, -3);
        lua_pop(data->L, 1);
      }
      // At this point, the stack:
      // top: index/hash key
      //    : table

      int want_value = 1;
      // Invoke the checkpath method if possible
      if (data->pos_ref != LUA_NOREF) {
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->metatable);
        lua_getfield(data->L, -1, "checkpath");
        if (lua_type(data->L, -1) != LUA_TNIL) {
          // Call with the new table and the path as arguments
          lua_rawgeti(data->L, LUA_REGISTRYINDEX, state->lua_object_ref);
          lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->pos_ref);
          lua_call(data->L, 2, 1);
          want_value = lua_toboolean(data->L, -1);
        }
        lua_pop(data->L, 2);    // Discard the metatable and either the getfield result or retval
      }

      if (want_value) {
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, state->lua_object_ref);
        lua_settable(data->L, -3);
        lua_pop(data->L, 1);    // the table
      } else {
        lua_pop(data->L, 2);    // the index and table
      }

      break;

    default:
        DBG_PRINTF("Unhandled type %c\n", state->type);
        luaL_error(data->L, "Unhandled type");
        break;
    }

    data->min_needed = state->pos_begin;
}