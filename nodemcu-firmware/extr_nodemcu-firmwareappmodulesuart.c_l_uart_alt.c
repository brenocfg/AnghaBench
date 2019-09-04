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
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_uart_alt (unsigned int) ; 

__attribute__((used)) static int l_uart_alt( lua_State* L )
{
  unsigned set;

  set = luaL_checkinteger( L, 1 );

  platform_uart_alt( set );
  return 0;
}