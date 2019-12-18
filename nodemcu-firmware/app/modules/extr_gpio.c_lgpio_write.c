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
 unsigned int HIGH ; 
 unsigned int LOW ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gpio ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_gpio_write (unsigned int,unsigned int) ; 

__attribute__((used)) static int lgpio_write( lua_State* L )
{
  unsigned pin = luaL_checkinteger( L, 1 );
  unsigned level = luaL_checkinteger( L, 2 );

  MOD_CHECK_ID( gpio, pin );
  luaL_argcheck(L, level==HIGH || level==LOW, 2, "wrong level type" );

  platform_gpio_write(pin, level);
  return 0;
}