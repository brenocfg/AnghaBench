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
 scalar_t__ ANSWER_TIMEOUT ; 
 scalar_t__ lastTime ; 
 int /*<<< orphan*/  reset_rgb () ; 
 scalar_t__ timer_elapsed32 (scalar_t__) ; 

void matrix_scan_user(void) {
  if (lastTime > 0 && timer_elapsed32(lastTime) > ANSWER_TIMEOUT) {
    lastTime = 0;
    reset_rgb();
  }
}