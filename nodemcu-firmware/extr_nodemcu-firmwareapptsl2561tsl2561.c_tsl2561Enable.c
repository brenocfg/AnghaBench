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
typedef  int /*<<< orphan*/  tsl2561Error_t ;

/* Variables and functions */
 int TSL2561_COMMAND_BIT ; 
 int /*<<< orphan*/  TSL2561_CONTROL_POWERON ; 
 int /*<<< orphan*/  TSL2561_ERROR_NOINIT ; 
 int TSL2561_REGISTER_CONTROL ; 
 int /*<<< orphan*/  _tsl2561Initialised ; 
 int /*<<< orphan*/  tsl2561Write8 (int,int /*<<< orphan*/ ) ; 

tsl2561Error_t tsl2561Enable(void) {
	if (!_tsl2561Initialised)
		return TSL2561_ERROR_NOINIT;

	// Enable the device by setting the control bit to 0x03
	return tsl2561Write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL,
	TSL2561_CONTROL_POWERON);
}