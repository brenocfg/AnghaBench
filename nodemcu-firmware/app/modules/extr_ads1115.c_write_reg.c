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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  ads1115_i2c_id ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t write_reg(uint8_t ads_addr, uint8_t reg, uint16_t config) {
    platform_i2c_send_start(ads1115_i2c_id);
    platform_i2c_send_address(ads1115_i2c_id, ads_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
    platform_i2c_send_byte(ads1115_i2c_id, reg);
    platform_i2c_send_byte(ads1115_i2c_id, (uint8_t)(config >> 8));
    platform_i2c_send_byte(ads1115_i2c_id, (uint8_t)(config & 0xFF));
    platform_i2c_send_stop(ads1115_i2c_id);
}