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

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LED_MATRIX_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_LED_MATRIX_INIT_COMPLETE ; 
 scalar_t__ gcr_min_counter ; 
 int /*<<< orphan*/  issi3733_prepare_arrays () ; 
 int /*<<< orphan*/  led_matrix_prepare () ; 
 scalar_t__ v_5v_cat_hit ; 

void init(void) {
    DBGC(DC_LED_MATRIX_INIT_BEGIN);

    issi3733_prepare_arrays();

    led_matrix_prepare();

    gcr_min_counter = 0;
    v_5v_cat_hit    = 0;

    DBGC(DC_LED_MATRIX_INIT_COMPLETE);
}