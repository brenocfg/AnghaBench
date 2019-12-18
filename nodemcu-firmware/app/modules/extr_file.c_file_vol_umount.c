#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vol; } ;
typedef  TYPE_1__ volume_type ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vfs_umount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_vol_umount( lua_State *L )
{
  volume_type *vol = luaL_checkudata( L, 1, "file.vol" );
  luaL_argcheck( L, vol, 1, "volume expected" );

  lua_pushboolean( L, 0 <= vfs_umount( vol->vol ) );

  // invalidate vfs descriptor, it has been free'd anyway
  vol->vol = NULL;
  return 1;
}