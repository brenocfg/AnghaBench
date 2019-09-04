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
struct vfs_stat {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 size_t FS_OBJ_NAME_LEN ; 
 scalar_t__ VFS_RES_OK ; 
 size_t c_strlen (char const*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 char* vfs_basename (char const*) ; 
 scalar_t__ vfs_stat (char*,struct vfs_stat*) ; 

__attribute__((used)) static int file_exists( lua_State* L )
{
  size_t len;
  const char *fname = luaL_checklstring( L, 1, &len );
  const char *basename = vfs_basename( fname );
  luaL_argcheck(L, c_strlen(basename) <= FS_OBJ_NAME_LEN && c_strlen(fname) == len, 1, "filename invalid");

  struct vfs_stat stat;
  lua_pushboolean(L, vfs_stat((char *)fname, &stat) == VFS_RES_OK ? 1 : 0);

  return 1;
}