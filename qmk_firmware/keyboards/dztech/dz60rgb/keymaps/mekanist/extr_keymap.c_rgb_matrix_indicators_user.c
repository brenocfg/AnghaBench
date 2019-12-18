#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
#define  _LAYER1 131 
#define  _LAYER2 130 
#define  _LAYER3 129 
#define  _LAYER4 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_suspend_state ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_state ; 
 TYPE_1__ rgb_matrix_config ; 
 int /*<<< orphan*/  rgb_matrix_layer_helper (int,int,int) ; 
 int /*<<< orphan*/  rgb_matrix_set_color (int,int,int,int) ; 

void rgb_matrix_indicators_user(void)
{
	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
		case _LAYER1:
			rgb_matrix_layer_helper(0xFF, 0x00, 0x00); break;

		case _LAYER2:
			rgb_matrix_layer_helper(0x00, 0xFF, 0x00); break;

		case _LAYER4:
			rgb_matrix_layer_helper(0xFF, 0xFF, 0x00); break;
		}
	}

	if (this_led & (1 << USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	}

	switch (biton32(layer_state)) {
	case _LAYER3:
		if (this_led & (1 << USB_LED_NUM_LOCK)) {
			rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
		} else {
			rgb_matrix_set_color(13, 0x00, 0x00, 0x00);
		}

		rgb_matrix_set_color(0, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(1, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(1, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(2, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(3, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(4, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(5, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(6, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(7, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(8, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(9, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(10, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(11, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(12, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(14, 0x00, 0x00, 0xFF);
		rgb_matrix_set_color(15, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(16, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(17, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(18, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(19, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(20, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(21, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(22, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(23, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(24, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(25, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(26, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(27, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(28, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(29, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(30, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(31, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(32, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(33, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(34, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(35, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(36, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(37, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(38, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(39, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(40, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(41, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(43, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(44, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(45, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(46, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(47, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(48, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(49, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(50, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(51, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(52, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(53, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(54, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(55, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(56, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(57, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(58, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(59, 0xFF, 0x00, 0x00);
		rgb_matrix_set_color(60, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(61, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(62, 0x00, 0x00, 0x00);
		break;
	}
}