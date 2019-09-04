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
 int MCP4725_COMMAND_WRITE_DAC ; 
 int MCP4725_COMMAND_WRITE_DAC_EEPROM ; 
 int MCP4725_I2C_ADDR_BASE ; 
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int get_address (int /*<<< orphan*/ *,int) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mcp4725_i2c_id ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp4725_write(lua_State* L){

  uint8 i2c_address = MCP4725_I2C_ADDR_BASE;
  uint16 dac_value = 0;
  uint8  cmd_byte = 0;

  if(lua_istable(L, 1))
  {
    i2c_address = get_address(L, i2c_address);
    uint16 temp_var=0;
    lua_getfield(L, 1, "value");
    if (!lua_isnil(L, -1))
    {
      if( lua_isnumber(L, -1) )
      {
        temp_var = lua_tonumber(L, -1);
        if(temp_var >= 0 && temp_var<=4095){
          dac_value = temp_var<<4;
        }
        else
          return luaL_argerror( L, 1, "value: Valid range 0-4095" );
      }
      else
      {
        return luaL_argerror( L, 1, "value: Must be number" );
      }
    }
    else
    {
      return luaL_argerror( L, 1, "value: value is required" );
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "save");
    if (!lua_isnil(L, -1))
    {
      if( lua_isboolean(L, -1) )
      {
        if(lua_toboolean(L, -1)){
          cmd_byte |= MCP4725_COMMAND_WRITE_DAC_EEPROM;
        }
        else{
          cmd_byte |= MCP4725_COMMAND_WRITE_DAC;
        }
      }
      else
      {
        return luaL_argerror( L, 1, "save: must be boolean" );
      }
    }
    else
    {
      cmd_byte |= MCP4725_COMMAND_WRITE_DAC;
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "pwrdn");
    if (!lua_isnil(L, -1))
    {
      if( lua_isnumber(L, -1) )
      {
        temp_var = lua_tonumber(L, -1);
        if(temp_var >= 0 && temp_var <= 3){
          cmd_byte |= temp_var << 1;
        }
        else{
          return luaL_argerror( L, 1, "pwrdn: Valid range 0-3" );
        }
      }
      else
      {
        return luaL_argerror( L, 1, "pwrdn: Must be number" );
      }
    }
    lua_pop(L, 1);

 }
  uint8 *dac_value_byte = (uint8*) & dac_value;

  platform_i2c_send_start(mcp4725_i2c_id);
  platform_i2c_send_address(mcp4725_i2c_id, i2c_address, PLATFORM_I2C_DIRECTION_TRANSMITTER);
  platform_i2c_send_byte(mcp4725_i2c_id, cmd_byte);
  platform_i2c_send_byte(mcp4725_i2c_id, dac_value_byte[1]);
  platform_i2c_send_byte(mcp4725_i2c_id, dac_value_byte[0]);
  platform_i2c_send_stop(mcp4725_i2c_id);

  return 0;
}