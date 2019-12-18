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
 int /*<<< orphan*/  PLATFORM_I2C_SPEED_SLOW ; 
 int /*<<< orphan*/  TSL2561_ERROR_OK ; 
 int /*<<< orphan*/  _tsl2561Gain ; 
 int _tsl2561Initialised ; 
 int /*<<< orphan*/  _tsl2561IntegrationTime ; 
 int /*<<< orphan*/  platform_i2c_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsl2561SetTiming (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsl2561_i2c_id ; 

tsl2561Error_t tsl2561Init(uint8_t sda, uint8_t scl) {
	// Initialise I2C
	platform_i2c_setup(tsl2561_i2c_id, sda, scl, PLATFORM_I2C_SPEED_SLOW);

	_tsl2561Initialised = 1;

	// Set default integration time and gain
	tsl2561SetTiming(_tsl2561IntegrationTime, _tsl2561Gain);

	// Note: by default, the device is in power down mode on bootup

	return TSL2561_ERROR_OK;
}