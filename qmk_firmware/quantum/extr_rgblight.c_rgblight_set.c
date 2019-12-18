#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  enable; } ;
struct TYPE_5__ {scalar_t__ w; scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 int RGBLED_NUM ; 
 int /*<<< orphan*/  clipping_num_leds ; 
 int clipping_start_pos ; 
 size_t effect_end_pos ; 
 size_t effect_start_pos ; 
 TYPE_1__* led ; 
 int /*<<< orphan*/ * led_map ; 
 size_t pgm_read_byte (int /*<<< orphan*/ *) ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  ws2812_setleds (TYPE_1__*,int /*<<< orphan*/ ) ; 

void rgblight_set(void) {
    LED_TYPE *start_led;
    uint16_t  num_leds = clipping_num_leds;

    if (!rgblight_config.enable) {
        for (uint8_t i = effect_start_pos; i < effect_end_pos; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
#    ifdef RGBW
            led[i].w = 0;
#    endif
        }
    }
#    ifdef RGBLIGHT_LED_MAP
    LED_TYPE led0[RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[pgm_read_byte(&led_map[i])];
    }
    start_led = led0 + clipping_start_pos;
#    else
    start_led = led + clipping_start_pos;
#    endif
    ws2812_setleds(start_led, num_leds);
}