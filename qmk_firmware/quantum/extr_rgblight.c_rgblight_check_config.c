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
struct TYPE_2__ {scalar_t__ mode; scalar_t__ val; } ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_LIMIT_VAL ; 
 scalar_t__ RGBLIGHT_MODES ; 
 scalar_t__ RGBLIGHT_MODE_STATIC_LIGHT ; 
 TYPE_1__ rgblight_config ; 

void rgblight_check_config(void) {
    /* Add some out of bound checks for RGB light config */

    if (rgblight_config.mode < RGBLIGHT_MODE_STATIC_LIGHT) {
        rgblight_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
    } else if (rgblight_config.mode > RGBLIGHT_MODES) {
        rgblight_config.mode = RGBLIGHT_MODES;
    }

    if (rgblight_config.val > RGBLIGHT_LIMIT_VAL) {
        rgblight_config.val = RGBLIGHT_LIMIT_VAL;
    }
}