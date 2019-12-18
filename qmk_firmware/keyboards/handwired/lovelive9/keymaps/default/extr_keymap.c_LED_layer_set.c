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
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * aqours_color_h ; 
 int /*<<< orphan*/ * aqours_color_s ; 
 int /*<<< orphan*/ * aqours_color_v ; 
 int /*<<< orphan*/ * led ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void LED_layer_set(int aqours_index) {
  for (int c = 0; c < 9; c++) {
    sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index], (LED_TYPE *)&led[c]);
  }
  rgblight_set();
}