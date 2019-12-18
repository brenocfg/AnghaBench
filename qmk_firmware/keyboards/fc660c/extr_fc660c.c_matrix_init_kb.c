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
 int /*<<< orphan*/  ACTUATION_DEPTH_ADJUSTMENT ; 
 int /*<<< orphan*/  adjust_actuation_point (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

#ifdef ACTUATION_DEPTH_ADJUSTMENT
    adjust_actuation_point(ACTUATION_DEPTH_ADJUSTMENT);
#endif

	matrix_init_user();
}