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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pwm2_start () ; 

__attribute__((used)) static int lpwm2_start(lua_State *L) {
  if (!pwm2_start()) {
    luaL_error(L, "pwm2: currently platform timer1 is being used by another module.\n");
    lua_pushboolean(L, false);
  } else {
    lua_pushboolean(L, true);
  }
  return 1;
}