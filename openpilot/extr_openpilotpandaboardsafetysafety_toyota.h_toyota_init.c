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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 scalar_t__ controls_allowed ; 
 int toyota_actuation_limits ; 
 scalar_t__ toyota_camera_forwarded ; 
 int /*<<< orphan*/  toyota_dbc_eps_torque_factor ; 
 scalar_t__ toyota_giraffe_switch_1 ; 

__attribute__((used)) static void toyota_init(int16_t param) {
  controls_allowed = 0;
  toyota_actuation_limits = 1;
  toyota_giraffe_switch_1 = 0;
  toyota_camera_forwarded = 0;
  toyota_dbc_eps_torque_factor = param;
  #ifdef PANDA
    lline_relay_release();
  #endif
}