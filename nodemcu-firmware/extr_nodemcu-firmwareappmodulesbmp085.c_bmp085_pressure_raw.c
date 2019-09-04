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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  bmp085_i2c_addr ; 
 int /*<<< orphan*/  bmp085_i2c_id ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 
 int r8u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t bmp085_pressure_raw(int oss) {
    int32_t p;
    int32_t p1, p2, p3;

    platform_i2c_send_start(bmp085_i2c_id);
    platform_i2c_send_address(bmp085_i2c_id, bmp085_i2c_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
    platform_i2c_send_byte(bmp085_i2c_id, 0xF4);
    platform_i2c_send_byte(bmp085_i2c_id, 0x34 + 64 * oss);
    platform_i2c_send_stop(bmp085_i2c_id);

    // Wait for device to complete sampling
    switch (oss) {
        case 0: os_delay_us( 4500); break;
        case 1: os_delay_us( 7500); break;
        case 2: os_delay_us(13500); break;
        case 3: os_delay_us(25500); break;
    }

    p1 = r8u(bmp085_i2c_id, 0xF6);
    p2 = r8u(bmp085_i2c_id, 0xF7);
    p3 = r8u(bmp085_i2c_id, 0xF8);
    p = (p1 << 16) | (p2 << 8) | p3;
    p = p >> (8 - oss);

    return p;
}