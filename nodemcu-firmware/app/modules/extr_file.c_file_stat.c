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
struct TYPE_2__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  mon; int /*<<< orphan*/  year; } ;
struct vfs_stat {TYPE_1__ tm; scalar_t__ tm_valid; int /*<<< orphan*/  is_arch; int /*<<< orphan*/  is_sys; int /*<<< orphan*/  is_hidden; int /*<<< orphan*/  is_rdonly; int /*<<< orphan*/  is_dir; int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TIMEDEF_DAY ; 
 int /*<<< orphan*/  FILE_TIMEDEF_HOUR ; 
 int /*<<< orphan*/  FILE_TIMEDEF_MIN ; 
 int /*<<< orphan*/  FILE_TIMEDEF_MON ; 
 int /*<<< orphan*/  FILE_TIMEDEF_SEC ; 
 int /*<<< orphan*/  FILE_TIMEDEF_YEAR ; 
 size_t FS_OBJ_NAME_LEN ; 
 scalar_t__ VFS_RES_OK ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ vfs_stat (char*,struct vfs_stat*) ; 

__attribute__((used)) static int file_stat( lua_State* L )
{
  size_t len;
  const char *fname = luaL_checklstring( L, 1, &len );
  luaL_argcheck( L, strlen(fname) <= FS_OBJ_NAME_LEN && strlen(fname) == len, 1, "filename invalid" );

  struct vfs_stat stat;
  if (vfs_stat( (char *)fname, &stat ) != VFS_RES_OK) {
    lua_pushnil( L );
    return 1;
  }

  lua_createtable( L, 0, 7 );

  lua_pushinteger( L, stat.size );
  lua_setfield( L, -2, "size" );

  lua_pushstring( L, stat.name );
  lua_setfield( L, -2, "name" );

  lua_pushboolean( L, stat.is_dir );
  lua_setfield( L, -2, "is_dir" );

  lua_pushboolean( L, stat.is_rdonly );
  lua_setfield( L, -2, "is_rdonly" );

  lua_pushboolean( L, stat.is_hidden );
  lua_setfield( L, -2, "is_hidden" );

  lua_pushboolean( L, stat.is_sys );
  lua_setfield( L, -2, "is_sys" );

  lua_pushboolean( L, stat.is_arch );
  lua_setfield( L, -2, "is_arch" );

  // time stamp as sub-table
  lua_createtable( L, 0, 6 );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.year : FILE_TIMEDEF_YEAR );
  lua_setfield( L, -2, "year" );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.mon : FILE_TIMEDEF_MON );
  lua_setfield( L, -2, "mon" );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.day : FILE_TIMEDEF_DAY );
  lua_setfield( L, -2, "day" );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.hour : FILE_TIMEDEF_HOUR );
  lua_setfield( L, -2, "hour" );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.min : FILE_TIMEDEF_MIN );
  lua_setfield( L, -2, "min" );

  lua_pushinteger( L, stat.tm_valid ? stat.tm.sec : FILE_TIMEDEF_SEC );
  lua_setfield( L, -2, "sec" );

  lua_setfield( L, -2, "time" );

  return 1;
}