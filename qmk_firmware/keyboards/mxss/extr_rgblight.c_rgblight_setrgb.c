#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t r; size_t g; size_t b; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 size_t RGBLED_NUM ; 
 TYPE_2__* led ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b) {
  if (!rgblight_config.enable) { return; }

  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    led[i].r = r;
    led[i].g = g;
    led[i].b = b;
  }
  rgblight_set();
}