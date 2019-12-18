#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_3__ {scalar_t__ null_ref; } ;
typedef  TYPE_1__ ENC_DATA ;

/* Variables and functions */
 scalar_t__ LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  LUA_TBOOLEAN 132 
#define  LUA_TLIGHTUSERDATA 131 
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_equal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void encode_lua_object(lua_State *L, ENC_DATA *data, int argno, const char *prefix, const char *suffix) {
  luaL_Buffer b;
  luaL_buffinit(L, &b);

  luaL_addstring(&b, prefix);

  int type = lua_type(L, argno);

  if (type == LUA_TSTRING) {
    // Check to see if it is the NULL value
    if (data->null_ref != LUA_REFNIL) {
      lua_rawgeti(L, LUA_REGISTRYINDEX, data->null_ref);
      if (lua_equal(L, -1, -2)) {
        type = LUA_TNIL;
      }
      lua_pop(L, 1);
    }
  }

  switch (type) {
    default:
      luaL_error(L, "Cannot encode type %d", type);
      break;

    case LUA_TLIGHTUSERDATA:
    case LUA_TNIL:
      luaL_addstring(&b, "null");
      break;

    case LUA_TBOOLEAN:
      luaL_addstring(&b, lua_toboolean(L, argno) ? "true" : "false");
      break;

    case LUA_TNUMBER:
    {
      lua_pushvalue(L, argno);
      size_t len;
      const char *str = lua_tolstring(L, -1, &len);
      char value[len + 1];
      strcpy(value, str);
      lua_pop(L, 1);
      luaL_addstring(&b, value);
      break;
    }

    case LUA_TSTRING:
    {
      luaL_addchar(&b, '"');
      size_t len;
      const char *str = lua_tolstring(L, argno, &len);
      while (len > 0) {
        if ((*str & 0xff) < 0x20) {
          char value[8];
          value[0] = '\\';

          char *d = value + 1;

          switch(*str) {
            case '\f':
              *d++ = 'f';
              break;
            case '\n':
              *d++ = 'n';
              break;
            case '\t':
              *d++ = 't';
              break;
            case '\r':
              *d++ = 'r';
              break;
            case '\b':
              *d++ = 'b';
              break;

            default:
              *d++ = 'u';
              *d++ = '0';
              *d++ = '0';
              *d++ = "0123456789abcdef"[(*str >> 4) & 0xf];
              *d++ = "0123456789abcdef"[(*str     ) & 0xf];
              break;

          }
          *d = '\0';
          luaL_addstring(&b, value);
        } else if (*str == '"') {
          luaL_addstring(&b, "\\\"");
        } else {
          luaL_addchar(&b, *str);
        }
        str++;
        len--;
      }
      luaL_addchar(&b, '"');
      break;
    }
  }

  luaL_addstring(&b, suffix);
  luaL_pushresult(&b);
}