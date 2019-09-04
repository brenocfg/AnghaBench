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
 scalar_t__ file_obj_map ; 
 scalar_t__ file_vol_map ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 

int luaopen_file( lua_State *L ) {
  luaL_rometatable( L, "file.vol",  (void *)file_vol_map );
  luaL_rometatable( L, "file.obj",  (void *)file_obj_map );
  return 0;
}