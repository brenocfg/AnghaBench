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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ tsl2561Error_t ;

/* Variables and functions */
 int TSL2561_COMMAND_BIT ; 
 scalar_t__ TSL2561_ERROR_NOINIT ; 
 scalar_t__ TSL2561_ERROR_OK ; 
#define  TSL2561_INTEGRATIONTIME_101MS 129 
#define  TSL2561_INTEGRATIONTIME_13MS 128 
 int TSL2561_REGISTER_CHAN0_LOW ; 
 int TSL2561_REGISTER_CHAN1_LOW ; 
 int TSL2561_WORD_BIT ; 
 int /*<<< orphan*/  _tsl2561Initialised ; 
 int _tsl2561IntegrationTime ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 scalar_t__ tsl2561Disable () ; 
 scalar_t__ tsl2561Enable () ; 
 scalar_t__ tsl2561Read16 (int,int /*<<< orphan*/ *) ; 

tsl2561Error_t tsl2561GetLuminosity(uint16_t *broadband, uint16_t *ir) {
	if (!_tsl2561Initialised)
		return TSL2561_ERROR_NOINIT;

	tsl2561Error_t error = TSL2561_ERROR_OK;

	// Enable the device by setting the control bit to 0x03
	error = tsl2561Enable();
	if (error)
		return error;

	// Wait x ms for ADC to complete
	switch (_tsl2561IntegrationTime) {
	case TSL2561_INTEGRATIONTIME_13MS:
		os_delay_us(14000); //systickDelay(14);
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		os_delay_us(102000); //systickDelay(102);
		break;
	default:
		os_delay_us(404000); //systickDelay(404);
		break;
	}

	// Reads two byte value from channel 0 (visible + infrared)
	error = tsl2561Read16(
	TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW, broadband);
	if (error)
		return error;

	// Reads two byte value from channel 1 (infrared)
	error = tsl2561Read16(
	TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW, ir);
	if (error)
		return error;

	// Turn the device off to save power
	error = tsl2561Disable();
	if (error)
		return error;

	return error;
}