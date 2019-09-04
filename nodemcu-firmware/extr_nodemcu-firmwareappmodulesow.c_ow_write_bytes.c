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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  onewire_write_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow ; 

__attribute__((used)) static int ow_write_bytes( lua_State *L )
{
  int power = 0;
  size_t datalen;
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( ow, id );

  const uint8_t *pdata = luaL_checklstring( L, 2, &datalen );

  if(lua_isnumber(L, 3))
    power = lua_tointeger(L, 3);
  if(power!=0)
    power = 1;

  onewire_write_bytes((uint8_t)id, pdata, (uint16_t)datalen, (uint8_t)power);

  return 0;
}