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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ RGBLED_NUM ; 
 scalar_t__ effect_end_pos ; 
 scalar_t__ effect_num_leds ; 
 scalar_t__ effect_start_pos ; 

void rgblight_set_effect_range(uint8_t start_pos, uint8_t num_leds) {
    if (start_pos >= RGBLED_NUM) return;
    if (start_pos + num_leds > RGBLED_NUM) return;
    effect_start_pos = start_pos;
    effect_end_pos   = start_pos + num_leds;
    effect_num_leds  = num_leds;
}