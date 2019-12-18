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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setCalibration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xpt2046_setCalibration( lua_State* L ) {
  int32_t a = luaL_checkinteger( L, 1 );
  int32_t b = luaL_checkinteger( L, 2 );
  int32_t c = luaL_checkinteger( L, 3 );
  int32_t d = luaL_checkinteger( L, 4 );
  setCalibration(a,b,c,d);
  return 0;
}