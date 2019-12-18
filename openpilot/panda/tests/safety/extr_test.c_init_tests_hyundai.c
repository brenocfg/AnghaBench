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
 scalar_t__ hyundai_desired_torque_last ; 
 scalar_t__ hyundai_rt_torque_last ; 
 TYPE_1__ hyundai_torque_driver ; 
 scalar_t__ hyundai_ts_last ; 
 int /*<<< orphan*/  init_tests () ; 
 int /*<<< orphan*/  set_timer (int /*<<< orphan*/ ) ; 

void init_tests_hyundai(void){
  init_tests();
  hyundai_torque_driver.min = 0;
  hyundai_torque_driver.max = 0;
  hyundai_desired_torque_last = 0;
  hyundai_rt_torque_last = 0;
  hyundai_ts_last = 0;
  set_timer(0);
}