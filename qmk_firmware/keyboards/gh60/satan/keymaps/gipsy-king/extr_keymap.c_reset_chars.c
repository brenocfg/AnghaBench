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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ RGBLED_NUM ; 
 scalar_t__ cursor_pos ; 
 int /*<<< orphan*/  rgblight_sethsv_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void reset_chars(void) {
  // flush the whole thing, gets rid of previous animations
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    // don't flicker the cursor if bar was empty on reset_timer
    if (i == 0 && cursor_pos == 0) {
        continue;
    }
    rgblight_sethsv_at(0, 0, 0, i);
  }
  cursor_pos = 0;
}