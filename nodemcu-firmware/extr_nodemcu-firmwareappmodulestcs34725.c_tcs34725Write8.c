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

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_I2C_DIRECTION_TRANSMITTER ; 
 int /*<<< orphan*/  TCS34725_ADDRESS ; 
 int /*<<< orphan*/  TCS34725_BUS_ID ; 
 int TCS34725_COMMAND_BIT ; 
 int /*<<< orphan*/  platform_i2c_send_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_i2c_send_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_i2c_send_stop (int /*<<< orphan*/ ) ; 

uint8_t tcs34725Write8 (uint8_t reg, uint8_t value)
{
	platform_i2c_send_start(TCS34725_BUS_ID);
	platform_i2c_send_address(TCS34725_BUS_ID, TCS34725_ADDRESS, PLATFORM_I2C_DIRECTION_TRANSMITTER);
	platform_i2c_send_byte(TCS34725_BUS_ID, TCS34725_COMMAND_BIT | reg );
	platform_i2c_send_byte(TCS34725_BUS_ID, value);
	platform_i2c_send_stop(TCS34725_BUS_ID);
	return 0;
}