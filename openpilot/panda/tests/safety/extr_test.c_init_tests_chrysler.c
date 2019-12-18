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
struct TYPE_2__ {scalar_t__ max; scalar_t__ min; } ;

/* Variables and functions */
 scalar_t__ chrysler_desired_torque_last ; 
 scalar_t__ chrysler_rt_torque_last ; 
 TYPE_1__ chrysler_torque_meas ; 
 scalar_t__ chrysler_ts_last ; 
 int /*<<< orphan*/  init_tests () ; 
 int /*<<< orphan*/  set_timer (int /*<<< orphan*/ ) ; 

void init_tests_chrysler(void){
  init_tests();
  chrysler_torque_meas.min = 0;
  chrysler_torque_meas.max = 0;
  chrysler_desired_torque_last = 0;
  chrysler_rt_torque_last = 0;
  chrysler_ts_last = 0;
  set_timer(0);
}