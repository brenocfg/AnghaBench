#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ fd; } ;
typedef  TYPE_1__ file_fd_ud ;

/* Variables and functions */
 size_t FS_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ file_fd ; 
 int /*<<< orphan*/  file_fd_ref ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 size_t strlen (char const*) ; 
 char* vfs_basename (char const*) ; 
 scalar_t__ vfs_open (char const*,char const*) ; 

__attribute__((used)) static int file_open( lua_State* L )
{
  size_t len;

  // unref last file descriptor to allow gc'ing if not kept by user script
  luaL_unref( L, LUA_REGISTRYINDEX, file_fd_ref );
  file_fd_ref = LUA_NOREF;

  const char *fname = luaL_checklstring( L, 1, &len );
  const char *basename = vfs_basename( fname );
  luaL_argcheck(L, strlen(basename) <= FS_OBJ_NAME_LEN && strlen(fname) == len, 1, "filename invalid");

  const char *mode = luaL_optstring(L, 2, "r");

  file_fd = vfs_open(fname, mode);

  if(!file_fd){
    lua_pushnil(L);
  } else {
    file_fd_ud *ud = (file_fd_ud *) lua_newuserdata( L, sizeof( file_fd_ud ) );
    ud->fd = file_fd;
    luaL_getmetatable( L, "file.obj" );
    lua_setmetatable( L, -2 );

    // store reference to opened file
    lua_pushvalue( L, -1 );
    file_fd_ref = luaL_ref( L, LUA_REGISTRYINDEX );
  }
  return 1;
}