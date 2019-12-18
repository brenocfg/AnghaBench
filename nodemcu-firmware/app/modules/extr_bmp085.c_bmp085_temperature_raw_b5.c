#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_2__ {int AC6; int AC5; int MC; int MD; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 TYPE_1__ bmp085_data ; 
 int /*<<< orphan*/  bmp085_i2c_addr ; 
 int /*<<< orphan*/  bmp085_i2c_id ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 
 int r16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t bmp085_temperature_raw_b5(void) {
    int16_t t, X1, X2;

    platform_i2c_send_start(bmp085_i2c_id);
    platform_i2c_send_address(bmp085_i2c_id, bmp085_i2c_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
    platform_i2c_send_byte(bmp085_i2c_id, 0xF4);
    platform_i2c_send_byte(bmp085_i2c_id, 0x2E);
    platform_i2c_send_stop(bmp085_i2c_id);

    // Wait for device to complete sampling
    os_delay_us(4500);

    t = r16(bmp085_i2c_id, 0xF6);
    X1 = ((t - bmp085_data.AC6) * bmp085_data.AC5) >> 15;
    X2 = (bmp085_data.MC << 11)/ (X1 + bmp085_data.MD);

    return X1 + X2;
}