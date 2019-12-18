#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ v; } ;
struct TYPE_4__ {TYPE_1__ hsv; } ;

/* Variables and functions */
 scalar_t__ RGB_MATRIX_MAXIMUM_BRIGHTNESS ; 
 int /*<<< orphan*/  RGB_MATRIX_VAL_STEP ; 
 int /*<<< orphan*/  eeconfig_update_rgb_matrix () ; 
 scalar_t__ qadd8 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ rgb_matrix_config ; 

void rgb_matrix_increase_val(void) {
    rgb_matrix_config.hsv.v = qadd8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP);
    if (rgb_matrix_config.hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    eeconfig_update_rgb_matrix();
}