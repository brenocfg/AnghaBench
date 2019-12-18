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
 int /*<<< orphan*/  animate_cursor (int) ; 
 scalar_t__ interval_time ; 
 int /*<<< orphan*/  last_timer ; 
 int /*<<< orphan*/  reset_chars () ; 
 scalar_t__ reset_time ; 
 int /*<<< orphan*/  reset_timer ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int timer_pos ; 
 int /*<<< orphan*/  timer_read () ; 

void matrix_scan_user(void) {
  if (timer_elapsed(reset_timer) > reset_time) {
      reset_chars();
      reset_timer = timer_read();
      return;
  }
  if (timer_elapsed(last_timer) < interval_time) {
    return;
  }
  last_timer += interval_time;
  timer_pos += 4;
  if (timer_pos >= 255) {
    timer_pos = 0;
    last_timer = timer_read();
  }
  animate_cursor(timer_pos);
}