#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jsonsl_state_st {int level; int type; int special_flags; void* lua_object_ref; scalar_t__ pos_begin; scalar_t__ pos_cur; } ;
typedef  TYPE_1__* jsonsl_t ;
typedef  int /*<<< orphan*/  jsonsl_action_t ;
struct TYPE_8__ {void* hkey_ref; void* null_ref; void* pos_ref; int complete; int /*<<< orphan*/  L; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ JSN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINTF (char*,...) ; 
 int JSONSL_SPECIALf_FALSE ; 
 int JSONSL_SPECIALf_NULL ; 
 int JSONSL_SPECIALf_NUMERIC ; 
 int JSONSL_SPECIALf_TRUE ; 
#define  JSONSL_T_HKEY 132 
#define  JSONSL_T_LIST 131 
#define  JSONSL_T_OBJECT 130 
#define  JSONSL_T_SPECIAL 129 
#define  JSONSL_T_STRING 128 
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 void* get_parent_object_ref () ; 
 int get_parent_object_used_count_pre_inc () ; 
 int /*<<< orphan*/  get_state_buffer (TYPE_2__*,struct jsonsl_state_st*) ; 
 int /*<<< orphan*/  jsonsl_strtype (int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* lua_ref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_unref (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  push_number (TYPE_2__*,struct jsonsl_state_st*) ; 
 int /*<<< orphan*/  push_string (TYPE_2__*,struct jsonsl_state_st*) ; 

__attribute__((used)) static void
cleanup_closing_element(jsonsl_t jsn,
                        jsonsl_action_t action,
                        struct jsonsl_state_st *state,
                        const char *at)
{
  JSN_DATA *data = (JSN_DATA *) jsn->data;
  DBG_PRINTF( "L%d: cc action %d state->type %s\n", state->level, action, jsonsl_strtype(state->type));
  DBG_PRINTF( "buf (%d - %d): '%.*s'\n", state->pos_begin, state->pos_cur, state->pos_cur - state->pos_begin, get_state_buffer(data, state));
  DBG_PRINTF( "at: '%s'\n", at);

 switch (state->type) {
   case JSONSL_T_HKEY:
      push_string(data, state);
      data->hkey_ref = lua_ref(data->L, 1);
      break;

   case JSONSL_T_STRING:
      lua_rawgeti(data->L, LUA_REGISTRYINDEX, get_parent_object_ref());
      if (data->hkey_ref == LUA_NOREF) {
        // list, so append
        lua_pushnumber(data->L, get_parent_object_used_count_pre_inc());
      } else {
        // object, so
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->hkey_ref);
        lua_unref(data->L, data->hkey_ref);
        data->hkey_ref = LUA_NOREF;
      }
      push_string(data, state);
      lua_settable(data->L, -3);
      lua_pop(data->L, 1);
      break;

   case JSONSL_T_SPECIAL:
      DBG_PRINTF("Special flags = 0x%x\n", state->special_flags);
      // need to deal with true/false/null

      if (state->special_flags & (JSONSL_SPECIALf_TRUE|JSONSL_SPECIALf_FALSE|JSONSL_SPECIALf_NUMERIC|JSONSL_SPECIALf_NULL)) {
        if (state->special_flags & JSONSL_SPECIALf_TRUE) {
          lua_pushboolean(data->L, 1);
        } else if (state->special_flags & JSONSL_SPECIALf_FALSE) {
          lua_pushboolean(data->L, 0);
        } else if (state->special_flags & JSONSL_SPECIALf_NULL) {
          DBG_PRINTF("Outputting null\n");
          lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->null_ref);
        } else if (state->special_flags & JSONSL_SPECIALf_NUMERIC) {
          push_number(data, state);
        }

        lua_rawgeti(data->L, LUA_REGISTRYINDEX, get_parent_object_ref());
        if (data->hkey_ref == LUA_NOREF) {
          // list, so append
          lua_pushnumber(data->L, get_parent_object_used_count_pre_inc());
        } else {
          // object, so
          lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->hkey_ref);
          lua_unref(data->L, data->hkey_ref);
          data->hkey_ref = LUA_NOREF;
        }
        lua_pushvalue(data->L, -3);
        lua_remove(data->L, -4);
        lua_settable(data->L, -3);
        lua_pop(data->L, 1);
      }
      break;
   case JSONSL_T_OBJECT:
   case JSONSL_T_LIST:
      lua_unref(data->L, state->lua_object_ref);
      state->lua_object_ref = LUA_NOREF;
      if (data->pos_ref != LUA_NOREF) {
        lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->pos_ref);
        lua_pushnumber(data->L, state->level);
        lua_pushnil(data->L);
        lua_settable(data->L, -3);
        lua_pop(data->L, 1);
      }
      if (state->level == 1) {
        data->complete = 1;
      }
      break;
 }
}