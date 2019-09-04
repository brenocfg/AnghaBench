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
 int LUA_MAXINPUT ; 
 scalar_t__ c_strcmp (char*,char*) ; 
 int /*<<< orphan*/  c_strlen (char*) ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_readline (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luai_writestringerror (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db_debug (lua_State *L) {
  for (;;) {
    char buffer[LUA_MAXINPUT];
#if defined(LUA_USE_STDIO)
    c_fputs("lua_debug> ", c_stderr);
    if (c_fgets(buffer, sizeof(buffer), c_stdin) == 0 ||
#else
//    luai_writestringerror("%s", "lua_debug>");
    if (lua_readline(L, buffer, "lua_debug>") == 0 ||
#endif
        c_strcmp(buffer, "cont\n") == 0)
      return 0;
    if (luaL_loadbuffer(L, buffer, c_strlen(buffer), "=(debug command)") ||
        lua_pcall(L, 0, 0, 0)) {
#if defined(LUA_USE_STDIO)
      c_fputs(lua_tostring(L, -1), c_stderr);
      c_fputs("\n", c_stderr);
#else
      luai_writestringerror("%s\n", lua_tostring(L, -1));
#endif
    }
    lua_settop(L, 0);  /* remove eventual returns */
  }
}