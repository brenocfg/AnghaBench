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
 int honda_brake_pressed_prev ; 
 int honda_fwd_brake ; 
 scalar_t__ honda_gas_prev ; 
 int honda_moving ; 
 int /*<<< orphan*/  init_tests () ; 

void init_tests_honda(void){
  init_tests();
  honda_moving = false;
  honda_brake_pressed_prev = false;
  honda_gas_prev = 0;
  honda_fwd_brake = false;
}