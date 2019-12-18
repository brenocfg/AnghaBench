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
 scalar_t__ cursor_pos ; 
 int /*<<< orphan*/  rgblight_sethsv_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void remove_char(void) {
  if (cursor_pos == 0) return;

  rgblight_sethsv_at(0, 0, 0, cursor_pos);
  rgblight_sethsv_at(0, 0, 0, cursor_pos - 1);
  cursor_pos -= 1;
}