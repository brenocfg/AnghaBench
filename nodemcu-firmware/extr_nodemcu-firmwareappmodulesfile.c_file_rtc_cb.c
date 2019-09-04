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
typedef  int /*<<< orphan*/  vfs_time ;
typedef  int /*<<< orphan*/  sint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_RES_OK ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_cb_ref ; 
 int /*<<< orphan*/  table2tm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sint32_t file_rtc_cb( vfs_time *tm )
{
  sint32_t res = VFS_RES_ERR;

  if (rtc_cb_ref != LUA_NOREF) {
    lua_State *L = lua_getstate();

    lua_rawgeti( L, LUA_REGISTRYINDEX, rtc_cb_ref );
    lua_call( L, 0, 1 );

    if (lua_type( L, lua_gettop( L ) ) == LUA_TTABLE) {
      table2tm( L, tm );
      res = VFS_RES_OK;
    }

    // pop item returned by callback
    lua_pop( L, 1 );
  }

  return res;
}