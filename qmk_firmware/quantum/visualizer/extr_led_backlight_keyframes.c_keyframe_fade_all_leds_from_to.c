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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  keyframe_animation_t ;
typedef  int /*<<< orphan*/  color_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_DISPLAY ; 
 int /*<<< orphan*/  LUMA2COLOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fade_led_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdispGClear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyframe_fade_all_leds_from_to(keyframe_animation_t* animation, uint8_t from, uint8_t to) {
    uint8_t luma  = fade_led_color(animation, from, to);
    color_t color = LUMA2COLOR(luma);
    gdispGClear(LED_DISPLAY, color);
}