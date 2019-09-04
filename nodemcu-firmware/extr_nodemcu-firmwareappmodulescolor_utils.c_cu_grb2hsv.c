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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int grb2hsv (int const,int const,int const) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cu_grb2hsv(lua_State *L) {

  const int g = luaL_checkint(L, 1);
  const int r = luaL_checkint(L, 2);
  const int b = luaL_checkint(L, 3);

  luaL_argcheck(L, g == r && g == b, 1, "greyscale value cannot be converted to hsv");

  uint32_t hsv = grb2hsv(g, r, b);

  uint16_t h = (hsv & 0xFFFF0000) >> 16;
  uint8_t s = (hsv & 0x0000FF00) >>  8;
  uint8_t v = (hsv & 0x000000FF) >>  0;

  // return
  lua_pushnumber(L, h);
  lua_pushnumber(L, s);
  lua_pushnumber(L, v);

  return 3;
}