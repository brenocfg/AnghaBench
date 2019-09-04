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
typedef  int /*<<< orphan*/  vfs_dir ;
struct vfs_stat {int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ VFS_RES_OK ; 
 int /*<<< orphan*/  luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfs_closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vfs_opendir (char*) ; 
 scalar_t__ vfs_readdir (int /*<<< orphan*/ *,struct vfs_stat*) ; 

__attribute__((used)) static int file_list( lua_State* L )
{
  vfs_dir  *dir;
  const char *pattern;
  struct vfs_stat stat;
  int pcres;

  lua_settop(L, 1);
  pattern = luaL_optstring(L, 1, NULL);   /* Pattern (arg) or nil (not) at 1 */

  dir = vfs_opendir("");
  if (dir == NULL) {
    return 0;
  }

  lua_newtable( L );                      /* Table at 2 */

  if (pattern) {
    /*
     * We know that pattern is a string, and so the "match" method will always
     * exist.  No need to check return value here
     */
    luaL_getmetafield( L, 1, "match" );  /* Function at 3 */
  }

  while (vfs_readdir(dir, &stat) == VFS_RES_OK) {
    if (pattern) {
      lua_settop( L, 3 );                 /* Ensure nothing else on stack */

      /* Construct and pcall(string.match,name,pattern) */
      lua_pushvalue( L, 3 );
      lua_pushstring( L, stat.name );
      lua_pushvalue( L, 1 );
      pcres = lua_pcall( L, 2, 1, 0 );
      if (pcres != 0) {
        vfs_closedir(dir);
        lua_error( L );
      }
      if (lua_isnil( L, -1 )) {
        continue;
      }
    }
    lua_pushinteger( L, stat.size );
    lua_setfield( L, 2, stat.name );
  }

  /* Shed everything back to Table */
  lua_settop( L, 2 );
  vfs_closedir(dir);
  return 1;
}