#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* sec; void* min; void* hour; void* day; void* mon; void* year; } ;
typedef  TYPE_1__ vfs_time ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TIMEDEF_DAY ; 
 int /*<<< orphan*/  FILE_TIMEDEF_HOUR ; 
 int /*<<< orphan*/  FILE_TIMEDEF_MIN ; 
 int /*<<< orphan*/  FILE_TIMEDEF_MON ; 
 int /*<<< orphan*/  FILE_TIMEDEF_SEC ; 
 int /*<<< orphan*/  FILE_TIMEDEF_YEAR ; 
 void* luaL_optint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void table2tm( lua_State *L, vfs_time *tm )
{
  int idx = lua_gettop( L );

  // extract items from table
  lua_getfield( L, idx, "year" );
  lua_getfield( L, idx, "mon" );
  lua_getfield( L, idx, "day" );
  lua_getfield( L, idx, "hour" );
  lua_getfield( L, idx, "min" );
  lua_getfield( L, idx, "sec" );

  tm->year = luaL_optint( L, ++idx, FILE_TIMEDEF_YEAR );
  tm->mon  = luaL_optint( L, ++idx, FILE_TIMEDEF_MON );
  tm->day  = luaL_optint( L, ++idx, FILE_TIMEDEF_DAY );
  tm->hour = luaL_optint( L, ++idx, FILE_TIMEDEF_HOUR );
  tm->min  = luaL_optint( L, ++idx, FILE_TIMEDEF_MIN );
  tm->sec  = luaL_optint( L, ++idx, FILE_TIMEDEF_SEC );

  // remove items from stack
  lua_pop( L, 6 );
}