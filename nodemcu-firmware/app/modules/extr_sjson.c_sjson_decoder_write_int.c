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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_4__ {scalar_t__ buffer_ref; int min_needed; int min_available; size_t buffer_len; scalar_t__ complete; scalar_t__ error; int /*<<< orphan*/  jsn; void* buffer; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  jsonsl_feed (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_addvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lua_ref (int /*<<< orphan*/ *,int) ; 
 int sjson_decoder_result_int (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sjson_free_working_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sjson_decoder_write_int(lua_State *L, int udata_pos, int string_pos) {
  JSN_DATA *data = (JSN_DATA *)luaL_checkudata(L, udata_pos, "sjson.decoder");
  size_t len;

  const char *str = luaL_checklstring(L, string_pos, &len);

  if (data->error) {
    luaL_error(L, "JSON parse error: previous call");
  }

  if (!data->complete) {
    data->L = L;

    // Merge into any existing buffer and deal with discard
    if (data->buffer_ref != LUA_NOREF) {
      luaL_Buffer b;
      luaL_buffinit(L, &b);

      lua_rawgeti(L, LUA_REGISTRYINDEX, data->buffer_ref);
      size_t prev_len;
      const char *prev_buffer = luaL_checklstring(L, -1, &prev_len);
      lua_pop(L, 1);              // But string still referenced so it cannot move
      int discard = data->min_needed - data->min_available;
      prev_buffer += discard;
      prev_len -= discard;
      if (prev_len > 0) {
        luaL_addlstring(&b, prev_buffer, prev_len);
      }
      data->min_available += discard;

      luaL_unref(L, LUA_REGISTRYINDEX, data->buffer_ref);
      data->buffer_ref = LUA_NOREF;

      lua_pushvalue(L, string_pos);
      luaL_addvalue(&b);
      luaL_pushresult(&b);
    } else {
      lua_pushvalue(L, string_pos);
    }

    size_t blen;
    data->buffer = luaL_checklstring(L, -1, &blen);
    data->buffer_len = blen;
    data->buffer_ref = lua_ref(L, 1);

    jsonsl_feed(data->jsn, str, len);

    if (data->error) {
      luaL_error(L, "JSON parse error: %s", data->error);
    }
  }

  if (data->complete) {
    // We no longer need the buffer
    sjson_free_working_data(L, data);

    return sjson_decoder_result_int(L, data);
  }

  return 0;
}