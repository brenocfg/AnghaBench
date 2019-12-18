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
 int /*<<< orphan*/  IS31FL3736_mono_set_brightness_all (int /*<<< orphan*/ ) ; 

void backlight_set_brightness_all( uint8_t value )
{
	IS31FL3736_mono_set_brightness_all( value );
}