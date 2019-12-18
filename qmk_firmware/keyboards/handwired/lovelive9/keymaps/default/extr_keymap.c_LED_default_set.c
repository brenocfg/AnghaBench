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

void LED_default_set(void) {

  sethsv(aqours_color_h[2], aqours_color_s[2], aqours_color_v[2], (LED_TYPE *)&led[0]);
  sethsv(aqours_color_h[7], aqours_color_s[7], aqours_color_v[7], (LED_TYPE *)&led[1]);
  sethsv(aqours_color_h[1], aqours_color_s[1], aqours_color_v[1], (LED_TYPE *)&led[2]);
  sethsv(aqours_color_h[5], aqours_color_s[5], aqours_color_v[5], (LED_TYPE *)&led[3]);
  sethsv(aqours_color_h[8], aqours_color_s[8], aqours_color_v[8], (LED_TYPE *)&led[4]);
  sethsv(aqours_color_h[6], aqours_color_s[6], aqours_color_v[6], (LED_TYPE *)&led[5]);
  sethsv(aqours_color_h[0], aqours_color_s[0], aqours_color_v[0], (LED_TYPE *)&led[6]);
  sethsv(aqours_color_h[4], aqours_color_s[4], aqours_color_v[4], (LED_TYPE *)&led[7]);
  sethsv(aqours_color_h[3], aqours_color_s[3], aqours_color_v[3], (LED_TYPE *)&led[8]);

  rgblight_set();

}