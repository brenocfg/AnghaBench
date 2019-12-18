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
 int /*<<< orphan*/ * led ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  sethsv (int,int,int,int /*<<< orphan*/ *) ; 

void set_colors(int r, int g, int b) {
  for(int i = 0; i<6; i++) {
    sethsv(r, g, b, (LED_TYPE *)&led[i]);
  }
  rgblight_set();
}