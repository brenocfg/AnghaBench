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
#define  KM_BLOWRAK 129 
#define  KM_QWERTY 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  ph_caps_led_off () ; 
 int /*<<< orphan*/  ph_caps_led_on () ; 
 int /*<<< orphan*/  ph_sclk_led_off () ; 
 int /*<<< orphan*/  ph_sclk_led_on () ; 

void matrix_scan_user(void)
{
	uint8_t layer = biton32(layer_state);
	switch (layer) {
		case KM_BLOWRAK:
			ph_caps_led_on();
			ph_sclk_led_off();
			break;
		case KM_QWERTY:
			ph_sclk_led_on();
			ph_caps_led_off();
			break;
	}
}