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
 scalar_t__ is_bspc_pressed ; 
 scalar_t__ is_ctl_pressed ; 
 scalar_t__ is_esc_pressed ; 
 int /*<<< orphan*/  reset_keyboard () ; 

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_esc_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}