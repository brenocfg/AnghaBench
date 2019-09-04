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
typedef  int uint8 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int MCP4725_I2C_ADDR_A0_MASK ; 
 int MCP4725_I2C_ADDR_A1_MASK ; 
 int MCP4725_I2C_ADDR_A2_MASK ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8 get_address(lua_State* L, uint8 i2c_address){
  uint8 addr_temp = i2c_address;
  uint16 temp_var = 0;
  lua_getfield(L, 1, "A2");
  if (!lua_isnil(L, -1))
  {
    if( lua_isnumber(L, -1) )
    {
      temp_var = lua_tonumber(L, -1);
      if(temp_var < 2){
        temp_var = MCP4725_I2C_ADDR_A2_MASK & (temp_var << 2);
        addr_temp|=temp_var;
      }
      else
        return luaL_argerror( L, 1, "A2: Must be 0 or 1" );
    }
    else
    {
      return luaL_argerror( L, 1, "A2: Must be number" );
    }
  }
  lua_pop(L, 1);

  lua_getfield(L, 1, "A1");
  if (!lua_isnil(L, -1))
  {
    if( lua_isnumber(L, -1) )
    {
      temp_var = lua_tonumber(L, -1);
      if(temp_var < 2){
        temp_var = MCP4725_I2C_ADDR_A1_MASK & (temp_var << 1);
        addr_temp|=temp_var;
      }
      else
        return luaL_argerror( L, 1, "A1: Must be 0 or 1" );
    }
    else
    {
      return luaL_argerror( L, 1, "A1: Must be number" );
    }
  }
  lua_pop(L, 1);

  lua_getfield(L, 1, "A0");
  if (!lua_isnil(L, -1))
  {
    if( lua_isnumber(L, -1) )
    {
      temp_var = lua_tonumber(L, -1);
      if(temp_var<2){
        temp_var = MCP4725_I2C_ADDR_A0_MASK & (temp_var);
        addr_temp|=temp_var;
      }
      else
        return luaL_argerror( L, 1, "A0: Must be 0 or 1" );
    }
    else
    {
      return luaL_argerror( L, 1, "A0: Must be number" );
    }
  }
  lua_pop(L, 1);

  return addr_temp;
}