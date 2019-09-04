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
 int bosch_hardware ; 
 scalar_t__ controls_allowed ; 
 int honda_alt_brake_msg ; 

__attribute__((used)) static void honda_init(int16_t param) {
  controls_allowed = 0;
  bosch_hardware = false;
  honda_alt_brake_msg = false;
  #ifdef PANDA
    lline_relay_release();
  #endif
}