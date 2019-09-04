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
 scalar_t__ brake_prev ; 
 scalar_t__ ego_speed ; 
 scalar_t__ gas_interceptor_detected ; 
 scalar_t__ gas_prev ; 

void init_tests_honda(void){
  ego_speed = 0;
  gas_interceptor_detected = 0;
  brake_prev = 0;
  gas_prev = 0;
}