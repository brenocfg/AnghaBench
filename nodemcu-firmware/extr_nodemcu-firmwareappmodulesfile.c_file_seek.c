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
#define  VFS_SEEK_CUR 130 
#define  VFS_SEEK_END 129 
#define  VFS_SEEK_SET 128 
 int /*<<< orphan*/  argpos ; 
 int /*<<< orphan*/  fd ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const* const*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 long luaL_optlong (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int vfs_lseek (int /*<<< orphan*/ ,long,int const) ; 
 int /*<<< orphan*/  vfs_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_seek (lua_State *L)
{
  GET_FILE_OBJ;

  static const int mode[] = {VFS_SEEK_SET, VFS_SEEK_CUR, VFS_SEEK_END};
  static const char *const modenames[] = {"set", "cur", "end", NULL};
  if(!fd)
    return luaL_error(L, "open a file first");
  int op = luaL_checkoption(L, argpos, "cur", modenames);
  long offset = luaL_optlong(L, ++argpos, 0);
  op = vfs_lseek(fd, offset, mode[op]);
  if (op < 0)
    lua_pushnil(L);  /* error */
  else
    lua_pushinteger(L, vfs_tell(fd));
  return 1;
}