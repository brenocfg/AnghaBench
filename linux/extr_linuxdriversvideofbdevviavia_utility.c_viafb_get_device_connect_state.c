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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_Device ; 
 int /*<<< orphan*/  DVI_Device ; 
 int /*<<< orphan*/  LCD_Device ; 
 scalar_t__ viafb_dvi_sense () ; 
 int /*<<< orphan*/  viafb_lcd_get_mobile_state (int*) ; 

void viafb_get_device_connect_state(u32 *connect_state)
{
	bool mobile = false;

	*connect_state = CRT_Device;

	if (viafb_dvi_sense())
		*connect_state |= DVI_Device;

	viafb_lcd_get_mobile_state(&mobile);
	if (mobile)
		*connect_state |= LCD_Device;
}