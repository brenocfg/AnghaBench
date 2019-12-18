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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int MCP4725_I2C_ADDR_BASE ; 
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_RECEIVER ; 
 int get_address (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mcp4725_i2c_id ; 
 int platform_i2c_recv_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp4725_read(lua_State* L){
  uint8 i2c_address = MCP4725_I2C_ADDR_BASE;
  uint8 recieve_buffer[5] = {0};

  if(lua_istable(L, 1))
   {
    i2c_address = get_address(L, i2c_address);
   }

  platform_i2c_send_start(mcp4725_i2c_id);
  platform_i2c_send_address(mcp4725_i2c_id, i2c_address, PLATFORM_I2C_DIRECTION_RECEIVER);
  for(int i=0;i<5;i++){
    recieve_buffer[i] = platform_i2c_recv_byte(mcp4725_i2c_id, 1);
  }
  platform_i2c_send_stop(mcp4725_i2c_id);

  lua_pushnumber(L, (recieve_buffer[0] & 0x06)>>1);
  lua_pushnumber(L, (recieve_buffer[1] << 4) | (recieve_buffer[2] >> 4));
  lua_pushnumber(L, (recieve_buffer[3] & 0x60) >> 5);
  lua_pushnumber(L, ((recieve_buffer[3] & 0xf) << 8) | recieve_buffer[4]);
  lua_pushnumber(L, (recieve_buffer[0] & 0x80) >> 7);
  lua_pushnumber(L, (recieve_buffer[0] & 0x40) >> 6);

  return 6;
}