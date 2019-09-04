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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vfs_fsinfo (char*,int*,int*) ; 

__attribute__((used)) static int file_fsinfo( lua_State* L )
{
  u32_t total, used;
  if (vfs_fsinfo("", &total, &used)) {
    return luaL_error(L, "file system failed");
  }
  NODE_DBG("total: %d, used:%d\n", total, used);
  if(total>0x7FFFFFFF || used>0x7FFFFFFF || used > total)
  {
    return luaL_error(L, "file system error");
  }
  lua_pushinteger(L, total-used);
  lua_pushinteger(L, used);
  lua_pushinteger(L, total);
  return 3;
}