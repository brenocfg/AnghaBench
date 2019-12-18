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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ rgblight_get_hue () ; 
 int /*<<< orphan*/  rgblight_get_sat () ; 
 int /*<<< orphan*/  rgblight_get_val () ; 
 int /*<<< orphan*/  rgblight_sethsv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void make_it_pink_blue(void) {
    uint16_t blue_hue = 210;
    uint16_t pink_hue = 315;

    /* key is pressed */
    uint16_t hue = rgblight_get_hue();
    uint8_t sat = rgblight_get_sat();
    uint8_t val = rgblight_get_val();

    if (hue != blue_hue)
        rgblight_sethsv(blue_hue, sat, val);
    else
        rgblight_sethsv(pink_hue, sat, val);
}