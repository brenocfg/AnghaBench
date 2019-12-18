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
 int BL_BLUE ; 
 int BL_GREEN ; 
 int BL_RED ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void backlight_set(uint8_t level)
{
	// Set the RGB color
	switch (level)
	{
	case 0:
		// Off
		BL_RED = 0xFFFF;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0xFFFF;
		break;
	case 1:
		// Red
		BL_RED = 0x0000;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0xFFFF;
		break;
	case 2:
		// Green
		BL_RED = 0xFFFF;
		BL_GREEN = 0x0000;
		BL_BLUE = 0xFFFF;
		break;
	case 3:
		// Blue
		BL_RED = 0xFFFF;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0x0000;
		break;
	case 4:
		// Magenta
		BL_RED = 0x4000;
		BL_GREEN = 0x4000;
		BL_BLUE = 0x4000;
		break;
	case 5:
		// Purple
		BL_RED = 0x0000;
		BL_GREEN = 0xFFFF;
		BL_BLUE = 0x0000;
		break;
	case 6:
		// Yellow
		BL_RED = 0x0000;
		BL_GREEN = 0x0000;
		BL_BLUE = 0xFFFF;
		break;
	default:
		xprintf("Unknown level: %d\n", level);
	}
}