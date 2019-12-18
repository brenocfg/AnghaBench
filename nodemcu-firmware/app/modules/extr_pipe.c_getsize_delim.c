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

/* Variables and functions */
 int CHAR_DELIM ; 
 int CHAR_DELIM_KEEP ; 
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char getsize_delim (lua_State *L, int ndx, int *len) {     // [-0, +0, v]
  char delim;
  int  n;
  if( lua_type( L, ndx ) == LUA_TNUMBER ) {
    n = luaL_checkinteger( L, ndx );
    luaL_argcheck(L, n > 0, ndx, "invalid chunk size");
    delim = '\0';
  } else if (lua_isnil(L, ndx)) {
    n = CHAR_DELIM;
    delim = '\n';
  } else {
    size_t ldelim;
    const char *s = lua_tolstring( L, 2, &ldelim);
    n = ldelim == 2 && s[1] == '+' ? CHAR_DELIM_KEEP : CHAR_DELIM ;
    luaL_argcheck(L, ldelim + n == 0, ndx, "invalid delimiter");
    delim = s[0];
  }
  if (len)
    *len = n;
  return delim;
}