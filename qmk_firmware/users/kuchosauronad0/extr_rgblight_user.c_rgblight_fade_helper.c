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
 scalar_t__ RGBLIGHT_VAL_STEP ; 
 int /*<<< orphan*/  rgblight_decrease_val () ; 
 int /*<<< orphan*/  rgblight_increase_val () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void rgblight_fade_helper(bool direction){
  // true: increase val = fade in 
  // false: decrease val = fade out
  for (uint8_t index = 0; index <  RGBLIGHT_VAL_STEP ; index++) {
    direction ? rgblight_increase_val()  : rgblight_decrease_val();
    wait_ms(5);
  }
}