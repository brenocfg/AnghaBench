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
 char* findfile (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  loaderror (int /*<<< orphan*/ *,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_loadfile (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ luaL_loadfsfile (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int loader_Lua (lua_State *L) {
  const char *filename;
  const char *name = luaL_checkstring(L, 1);
  filename = findfile(L, name, "path");
  if (filename == NULL) return 1;  /* library not found in this path */
#ifdef LUA_CROSS_COMPILER
  if (luaL_loadfile(L, filename) != 0)
#else
  if (luaL_loadfsfile(L, filename) != 0)
#endif
    loaderror(L, filename);
  return 1;  /* library loaded successfully */
}