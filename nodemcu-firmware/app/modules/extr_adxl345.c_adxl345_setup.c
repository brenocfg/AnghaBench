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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  adxl345_i2c_addr ; 
 int /*<<< orphan*/  adxl345_i2c_id ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 
 int r8u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adxl345_setup(lua_State* L) {
    uint8_t  devid;

    devid = r8u(adxl345_i2c_id, 0x00);

    if (devid != 229) {
        return luaL_error(L, "device not found");
    }

    // Enable sensor
    platform_i2c_send_start(adxl345_i2c_id);
    platform_i2c_send_address(adxl345_i2c_id, adxl345_i2c_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
    platform_i2c_send_byte(adxl345_i2c_id, 0x2D);
    platform_i2c_send_byte(adxl345_i2c_id, 0x08);
    platform_i2c_send_stop(adxl345_i2c_id);

    return 0;
}