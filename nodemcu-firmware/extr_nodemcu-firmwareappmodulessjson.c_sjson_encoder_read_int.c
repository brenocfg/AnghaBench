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
struct TYPE_4__ {scalar_t__ current_str_ref; int offset; } ;
typedef  TYPE_1__ ENC_DATA ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_unref (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sjson_encoder_make_next_chunk (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sjson_encoder_read_int(lua_State *L, ENC_DATA *data, int readsize) {
  luaL_Buffer b;
  luaL_buffinit(L, &b);

  size_t len;

  do {
    // Fill the buffer with (up to) readsize characters
    if (data->current_str_ref != LUA_NOREF) {
      // this is not allowed
      lua_rawgeti(L, LUA_REGISTRYINDEX, data->current_str_ref);
      const char *str = lua_tolstring(L, -1, &len);

      lua_pop(L, 1); // Note that we still have the string referenced so it can't go away

      int amnt = len - data->offset;;
      if (amnt > readsize) {
        amnt = readsize;
      }
      luaL_addlstring(&b, str + data->offset, amnt);
      data->offset += amnt;
      readsize -= amnt;

      if (data->offset == len) {
        lua_unref(L, data->current_str_ref);
        data->current_str_ref = LUA_NOREF;
      }
    }

    if (readsize > 0) {
      // Make the next chunk
      sjson_encoder_make_next_chunk(L, data);
    }

  } while (readsize > 0 && data->current_str_ref != LUA_NOREF);

  luaL_pushresult(&b);

  lua_tolstring(L, -1, &len);

  if (len == 0) {
    // we have got to the end
    lua_pop(L, 1);
    return 0;
  }

  return 1;
}