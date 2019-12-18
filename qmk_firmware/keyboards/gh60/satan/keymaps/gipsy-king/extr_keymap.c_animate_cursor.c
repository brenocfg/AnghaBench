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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_pos ; 
 int fmin (int,int) ; 
 int /*<<< orphan*/  rgblight_get_hue () ; 
 int /*<<< orphan*/  rgblight_get_sat () ; 
 int /*<<< orphan*/  rgblight_sethsv_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void animate_cursor(uint16_t pos) {
  uint16_t value = pos < 196 ? fmin(255, pos * 16) : (255 - (pos * 2));
  rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), value, cursor_pos);
}