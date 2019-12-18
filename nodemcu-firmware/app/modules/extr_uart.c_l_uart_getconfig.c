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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_uart_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart ; 

__attribute__((used)) static int l_uart_getconfig( lua_State* L )
{
  uint32_t id, databits, parity, stopbits;
  uint32_t baud;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( uart, id );

  platform_uart_get_config(id, &baud, &databits, &parity, &stopbits);

  lua_pushinteger(L, baud);
  lua_pushinteger(L, databits);
  lua_pushinteger(L, parity);
  lua_pushinteger(L, stopbits);
  return 4;
}