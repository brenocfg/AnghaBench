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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 scalar_t__ HW_TYPE_WHITE_PANDA ; 
 int /*<<< orphan*/  PULL_DOWN ; 
 int /*<<< orphan*/  PULL_UP ; 
 int /*<<< orphan*/  detect_with_pull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_external_debug_serial ; 
 scalar_t__ hw_type ; 
 int is_entering_bootmode ; 

void detect_configuration(void) {
  // detect if external serial debugging is present
  has_external_debug_serial = detect_with_pull(GPIOA, 3, PULL_DOWN);

  #ifdef PANDA
    if(hw_type == HW_TYPE_WHITE_PANDA) {
      // check if the ESP is trying to put me in boot mode
      is_entering_bootmode = !detect_with_pull(GPIOB, 0, PULL_UP);
    } else {
      is_entering_bootmode = 0;
    }
  #else
    is_entering_bootmode = 0;
  #endif
}