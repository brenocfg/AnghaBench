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
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
struct TYPE_4__ {TYPE_1__ hsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGB_MATRIX_VAL_STEP ; 
 int /*<<< orphan*/  eeconfig_update_rgb_matrix () ; 
 int /*<<< orphan*/  qsub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ rgb_matrix_config ; 

void rgb_matrix_decrease_val(void) {
    rgb_matrix_config.hsv.v = qsub8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP);
    eeconfig_update_rgb_matrix();
}