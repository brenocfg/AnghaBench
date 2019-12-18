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
 int /*<<< orphan*/  HSV_GREEN ; 
 int /*<<< orphan*/  HSV_RED ; 
 int /*<<< orphan*/  fadeflash_leds (int /*<<< orphan*/ ) ; 
 scalar_t__ leader_succeed ; 

void leader_end(void) {
// pick color depending of success /fail
// fade leader_start from 100 to 0
// fade new color from  0 to 100 to 0
// fade old color from 0 to 100
#ifdef RGBLIGHT_ENABLE
  if (leader_succeed) {
    fadeflash_leds(HSV_GREEN);
  } else {
    fadeflash_leds(HSV_RED);
  }
#endif
}