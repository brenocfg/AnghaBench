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
struct TYPE_2__ {int /*<<< orphan*/  vol; } ;
typedef  TYPE_1__ volume_type ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfs_mount (char const*,int) ; 

__attribute__((used)) static int file_mount( lua_State *L )
{
  const char *ldrv = luaL_checkstring( L, 1 );
  int num = luaL_optint( L, 2, -1 );
  volume_type *vol = (volume_type *)lua_newuserdata( L, sizeof( volume_type ) );

  if (vol->vol = vfs_mount( ldrv, num )) {
    /* set its metatable */
    luaL_getmetatable(L, "file.vol");
    lua_setmetatable(L, -2);
    return 1;
  } else {
    // remove created userdata
    lua_pop( L, 1 );
    return 0;
  }
}