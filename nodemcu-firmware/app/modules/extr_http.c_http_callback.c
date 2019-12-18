#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int HTTP_STATUS_GENERIC_ERROR ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  dbg_printf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ http_callback_registry ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* strlen (char const*) ; 
 int /*<<< orphan*/  tolower (unsigned char) ; 

__attribute__((used)) static void http_callback( char * response, int http_status, char ** full_response_p )
{
  const char *full_response = full_response_p ? *full_response_p : NULL;

#if defined(HTTPCLIENT_DEBUG_ON)
  dbg_printf( "http_status=%d\n", http_status );
  if ( http_status != HTTP_STATUS_GENERIC_ERROR )
  {
    if (full_response != NULL) {
      dbg_printf( "strlen(full_response)=%d\n", strlen( full_response ) );
    }
    dbg_printf( "response=%s<EOF>\n", response );
  }
#endif
  if (http_callback_registry != LUA_NOREF)
  {
    lua_State *L = lua_getstate();

    lua_rawgeti(L, LUA_REGISTRYINDEX, http_callback_registry);

    lua_pushnumber(L, http_status);
    if ( http_status != HTTP_STATUS_GENERIC_ERROR && response)
    {
      lua_pushstring(L, response);
      lua_newtable(L);

      const char *p = full_response;

      // Need to skip the HTTP/1.1 header line
      while (*p && *p != '\n') {
        p++;
      }
      if (*p == '\n') {
        p++;
      }

      while (*p && *p != '\r' && *p != '\n') {
        const char *eol = p;
        while (*eol && *eol != '\r') {
          eol++;
        }

        const char *colon = p;
        while (*colon != ':' && colon < eol) {
          colon++;
        }

        if (*colon != ':') {
          break;
        }

        const char *value = colon + 1;
        while (*value == ' ') {
          value++;
        }

        luaL_Buffer b;
        luaL_buffinit(L, &b);
        while (p < colon) {
          luaL_addchar(&b, tolower((unsigned char) *p));
          p++;
        }
        luaL_pushresult(&b);

        lua_pushlstring(L, value, eol - value);
        lua_settable(L, -3);

        p = eol + 1;
        if (*p == '\n') {
          p++;
        }
      }
    }
    else
    {
      lua_pushnil(L);
      lua_pushnil(L);
    }

    if (full_response_p && *full_response_p) {
      free(*full_response_p);
      *full_response_p = NULL;
    }

    luaL_unref(L, LUA_REGISTRYINDEX, http_callback_registry);
    http_callback_registry = LUA_NOREF;

    lua_call(L, 3, 0); // With 3 arguments and 0 result
  }
}