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
typedef  int /*<<< orphan*/  tsl2561Error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  TSL2561_ERROR_OK ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsl2561Address ; 
 int /*<<< orphan*/  tsl2561_i2c_id ; 

tsl2561Error_t tsl2561Write8(uint8_t reg, uint8_t value) {
	platform_i2c_send_start(tsl2561_i2c_id);
	platform_i2c_send_address(tsl2561_i2c_id, tsl2561Address, PLATFORM_I2C_DIRECTION_TRANSMITTER);
	platform_i2c_send_byte(tsl2561_i2c_id, reg);
	platform_i2c_send_byte(tsl2561_i2c_id, value);
	platform_i2c_send_stop(tsl2561_i2c_id);
	return TSL2561_ERROR_OK;
}