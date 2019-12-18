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
 int /*<<< orphan*/  IS31FL3736_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS31FL3736_mono_set_led_control_register (int,int) ; 
 int /*<<< orphan*/  IS31FL3736_update_led_control_registers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSI_ADDR_DEFAULT ; 
 int /*<<< orphan*/  i2c_init () ; 

void backlight_init_drivers(void)
{
	// Initialize I2C
	i2c_init();
	IS31FL3736_init( ISSI_ADDR_DEFAULT );

	for ( uint8_t index = 0; index < 96; index++ )	{
		IS31FL3736_mono_set_led_control_register( index, true );
	}
	IS31FL3736_update_led_control_registers( ISSI_ADDR_DEFAULT, 0x00 );
}