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
 int /*<<< orphan*/  GET_FILE_OBJ ; 
 int /*<<< orphan*/  argpos ; 
 int /*<<< orphan*/  fd ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 size_t vfs_write (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int file_write( lua_State* L )
{
  GET_FILE_OBJ;

  if(!fd)
    return luaL_error(L, "open a file first");
  size_t l, rl;
  const char *s = luaL_checklstring(L, argpos, &l);
  rl = vfs_write(fd, s, l);
  if(rl==l)
    lua_pushboolean(L, 1);
  else
    lua_pushnil(L);
  return 1;
}