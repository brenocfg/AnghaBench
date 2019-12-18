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
typedef  unsigned long uint16_t ;

/* Variables and functions */
 unsigned long _DVORAK ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  rgblight_sethsv_goldenrod () ; 
 int /*<<< orphan*/  rgblight_sethsv_green () ; 

void update_rgblight(uint16_t layer) {
  if (layer & (1UL << _DVORAK)) {
    rgblight_sethsv_green();
  } else if (layer & (1UL << _QWERTY)) {
    rgblight_sethsv_goldenrod();
  }
}