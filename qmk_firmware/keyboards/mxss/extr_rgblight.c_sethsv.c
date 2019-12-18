#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int hue; int sat; } ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * CIE1931_CURVE ; 
 size_t RGBLIGHT_FLED1 ; 
 size_t RGBLIGHT_FLED2 ; 
 int RGBLIGHT_LIMIT_VAL ; 
 TYPE_1__* fled_hs ; 
 int /*<<< orphan*/ * led ; 
 int pgm_read_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrgb (int,int,int,int /*<<< orphan*/ *) ; 

void sethsv(uint16_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) {
  uint8_t r = 0, g = 0, b = 0, base, color;
  
  // if led is front leds, cache the hue and sat values
  if (led1 == &led[RGBLIGHT_FLED1]) {
      fled_hs[0].hue = hue;
      fled_hs[0].sat = sat;
  } else if (led1 == &led[RGBLIGHT_FLED2]) {
      fled_hs[1].hue = hue;
      fled_hs[1].sat = sat;
  }

  if (val > RGBLIGHT_LIMIT_VAL) {
      val=RGBLIGHT_LIMIT_VAL; // limit the val
  }

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    r = val;
    g = val;
    b = val;
  } else {
    base = ((255 - sat) * val) >> 8;
    color = (val - base) * (hue % 60) / 60;

    switch (hue / 60) {
      case 0:
        r = val;
        g = base + color;
        b = base;
        break;
      case 1:
        r = val - color;
        g = val;
        b = base;
        break;
      case 2:
        r = base;
        g = val;
        b = base + color;
        break;
      case 3:
        r = base;
        g = val - color;
        b = val;
        break;
      case 4:
        r = base + color;
        g = base;
        b = val;
        break;
      case 5:
        r = val;
        g = base;
        b = val - color;
        break;
    }
  }
  r = pgm_read_byte(&CIE1931_CURVE[r]);
  g = pgm_read_byte(&CIE1931_CURVE[g]);
  b = pgm_read_byte(&CIE1931_CURVE[b]);

  setrgb(r, g, b, led1);
}