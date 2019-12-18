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
#define  _BASE 130 
#define  _MEDIA 129 
#define  _SYMBOLS 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frenchdev_led_1_off () ; 
 int /*<<< orphan*/  frenchdev_led_1_on () ; 
 int /*<<< orphan*/  frenchdev_led_2_off () ; 
 int /*<<< orphan*/  frenchdev_led_2_on () ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    frenchdev_led_1_off();
    frenchdev_led_2_off();
    switch (layer) {
        case _BASE:
            frenchdev_led_2_on();
            break;
        case _SYMBOLS:
            frenchdev_led_1_on();
            break;
        case _MEDIA:
           frenchdev_led_1_on();
           frenchdev_led_2_on();
        default:
            // none
            break;
    }
}