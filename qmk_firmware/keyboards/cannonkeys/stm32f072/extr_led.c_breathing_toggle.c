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
 int /*<<< orphan*/  breathing_disable () ; 
 int /*<<< orphan*/  breathing_enable () ; 
 scalar_t__ is_breathing () ; 
 int /*<<< orphan*/  printf (char*) ; 

void breathing_toggle(void) {
  if (is_breathing()){
    printf("disable breathing\n");
    breathing_disable();
  } else {
    printf("enable breathing\n");
    breathing_enable();
  }
}