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

/* Variables and functions */
 unsigned int CRT_Device ; 
 unsigned int DVI_Device ; 
 unsigned int LCD_Device ; 
 unsigned int None_Device ; 

void viafb_get_gamma_support_state(int bpp, unsigned int *support_state)
{
	if (bpp == 8)
		*support_state = None_Device;
	else
		*support_state = CRT_Device | DVI_Device | LCD_Device;
}