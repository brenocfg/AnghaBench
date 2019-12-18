#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_4__ {void* b; void* g; void* r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 int RGBLED_NUM ; 
 TYPE_1__* led ; 
 int /*<<< orphan*/  rgblight_set () ; 
 TYPE_1__* shadowed_led ; 
 scalar_t__ user_rgb_mode ; 

void rgbflag(uint8_t r, uint8_t g, uint8_t b, uint8_t rr, uint8_t gg, uint8_t bb) {
  LED_TYPE *target_led = user_rgb_mode ? shadowed_led : led;
  for (int i = 0; i < RGBLED_NUM; i++)  {
    switch (i) {
    case 10: case 11:
      target_led[i].r = r;
      target_led[i].g = g;
      target_led[i].b = b;
      break;
    case 0: case 1:
      target_led[i].r = rr;
      target_led[i].g = gg;
      target_led[i].b = bb;
      break;
    default:
      target_led[i].r = 0;
      target_led[i].g = 0;
      target_led[i].b = 0;
      break;
    }
  }
  rgblight_set();
}