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
 int /*<<< orphan*/  I2C3733_Control_Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_power_down_kb () ; 

void suspend_power_down(void) {
#ifdef RGB_MATRIX_ENABLE
    I2C3733_Control_Set(0);  // Disable LED driver
#endif

    suspend_power_down_kb();
}