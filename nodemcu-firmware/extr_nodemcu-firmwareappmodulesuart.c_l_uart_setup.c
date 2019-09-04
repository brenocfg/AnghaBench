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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ platform_uart_setup (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uart ; 
 int uart0_echo ; 

__attribute__((used)) static int l_uart_setup( lua_State* L )
{
  uint32_t id, databits, parity, stopbits, echo = 1;
  uint32_t baud, res;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( uart, id );

  baud = luaL_checkinteger( L, 2 );
  databits = luaL_checkinteger( L, 3 );
  parity = luaL_checkinteger( L, 4 );
  stopbits = luaL_checkinteger( L, 5 );
  if(lua_isnumber(L,6)){
    echo = lua_tointeger(L,6);
    if(echo!=0)
      uart0_echo = true;
    else
      uart0_echo = false;
  }

  res = platform_uart_setup( id, baud, databits, parity, stopbits );
  lua_pushinteger( L, res );
  return 1;
}