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
 int /*<<< orphan*/  rgb_matrix_set_suspend_state (int) ; 
 int /*<<< orphan*/  suspend_power_down_user () ; 

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
        suspend_power_down_user();
}