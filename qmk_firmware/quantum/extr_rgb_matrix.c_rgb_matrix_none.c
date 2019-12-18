#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ effect_params_t ;

/* Variables and functions */
 scalar_t__ DRIVER_LED_TOTAL ; 
 int /*<<< orphan*/  RGB_MATRIX_USE_LIMITS (scalar_t__,scalar_t__) ; 
 scalar_t__ led_max ; 
 scalar_t__ led_min ; 
 int /*<<< orphan*/  rgb_matrix_set_color (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rgb_matrix_none(effect_params_t *params) {
    if (!params->init) {
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    return led_max < DRIVER_LED_TOTAL;
}