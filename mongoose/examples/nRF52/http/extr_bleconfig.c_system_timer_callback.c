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
typedef  int /*<<< orphan*/  iot_timer_time_in_ms_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_check_timeouts () ; 

__attribute__((used)) static void system_timer_callback(iot_timer_time_in_ms_t wall_clock_value)
{
  UNUSED_VARIABLE(wall_clock_value);
  sys_check_timeouts();
}