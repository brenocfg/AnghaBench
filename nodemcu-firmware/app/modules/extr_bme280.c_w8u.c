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

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  bme280_i2c_addr ; 
 int /*<<< orphan*/  bme280_i2c_id ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t w8u(uint8_t reg, uint8_t val) {
	platform_i2c_send_start(bme280_i2c_id);
	platform_i2c_send_address(bme280_i2c_id, bme280_i2c_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
	platform_i2c_send_byte(bme280_i2c_id, reg);
	platform_i2c_send_byte(bme280_i2c_id, val);
	platform_i2c_send_stop(bme280_i2c_id);
}