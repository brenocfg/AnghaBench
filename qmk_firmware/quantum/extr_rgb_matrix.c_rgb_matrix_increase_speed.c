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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGB_MATRIX_SPD_STEP ; 
 int /*<<< orphan*/  eeconfig_update_rgb_matrix () ; 
 int /*<<< orphan*/  qadd8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ rgb_matrix_config ; 

void rgb_matrix_increase_speed(void) {
    rgb_matrix_config.speed = qadd8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP);
    eeconfig_update_rgb_matrix();
}