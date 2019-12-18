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
 int /*<<< orphan*/  led_toggle (int,int) ; 

void set_layer_indicators(uint8_t layer) {
	
	switch (layer)
	{
		case 0:
			led_toggle(0, true);
			led_toggle(1, false);
			led_toggle(2, false);
			break;
		case 1:
			led_toggle(0, true);
			led_toggle(1, true);
			led_toggle(2, false);
			break;
		case 2:
			led_toggle(0, true);
			led_toggle(1, true);
			led_toggle(2, true);
			break;
		case 3:
			led_toggle(0, false);
			led_toggle(1, true);
			led_toggle(2, true);
			break;
		case 4:
			led_toggle(0, false);
			led_toggle(1, false);
			led_toggle(2, true);
			break;
		default:
			led_toggle(0, true);
			led_toggle(1, false);
			led_toggle(2, true);
			break;
	}
	
}