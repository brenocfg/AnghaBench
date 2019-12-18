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
 scalar_t__ IS_HOST_LED_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MAIN_COLOR ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 size_t biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int* layers_leds_map ; 
 int /*<<< orphan*/  rgb_matrix_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rgb_matrix_indicators_user(void) {

    // CapsLock Light
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(8, MAIN_COLOR[0], MAIN_COLOR[1], MAIN_COLOR[2]);
    }

    // Show Selected Layer
    rgb_matrix_set_color(layers_leds_map[biton32(layer_state)], MAIN_COLOR[0], MAIN_COLOR[1], MAIN_COLOR[2]);
}