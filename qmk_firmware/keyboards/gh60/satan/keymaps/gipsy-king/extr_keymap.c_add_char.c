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
 int RGBLED_NUM ; 
 int cursor_pos ; 
 int /*<<< orphan*/  reset_chars () ; 
 int /*<<< orphan*/  rgblight_get_hue () ; 
 int /*<<< orphan*/  rgblight_get_sat () ; 
 int /*<<< orphan*/  rgblight_get_val () ; 
 int /*<<< orphan*/  rgblight_sethsv_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void add_char(bool space) {
  if (cursor_pos == RGBLED_NUM - 1) {
    cursor_pos = 0;
    reset_chars();
    return;
  }

  if (space) {
    rgblight_sethsv_at(0, 0, 0, cursor_pos);
  } else {
    rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), cursor_pos);
  }
  cursor_pos += 1;
}