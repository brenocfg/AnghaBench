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
struct TYPE_3__ {size_t colorsPerLed; int size; int* values; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 int grb2hsv (int,int,int) ; 
 int hsv2grb (int,int,int) ; 
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_gradient(const char *gradient_spec, size_t length1) {

  ws2812_buffer * buffer = state->buffer;

  int segments = (length1 / buffer->colorsPerLed) - 1;
  int segmentSize = buffer->size / segments;

  uint8_t g1, r1, b1, g2, r2, b2;
  int i,j,k;

  g2 = *gradient_spec++;
  r2 = *gradient_spec++;
  b2 = *gradient_spec++;
  // skip non-rgb components
  for (j = 3; j < buffer->colorsPerLed; j++)
  {
    *gradient_spec++;
  }

  // reference to buffer memory
  uint8_t * p = &buffer->values[0];

  uint16_t h1,h2;
  uint8_t s,v,s1,v1,s2,v2;

  for (k = 0; k < segments; k++) {
    g1 = g2;
    r1 = r2;
    b1 = b2;
    uint32_t hsv1 = grb2hsv(g1, r1, b1);
    h1 = (hsv1 & 0xFFFF0000) >> 16;
    s1 = (hsv1 & 0x0000FF00) >> 8;
    v1 = (hsv1 & 0x000000FF);

    g2 = *gradient_spec++;
    r2 = *gradient_spec++;
    b2 = *gradient_spec++;
    for (j = 3; j < buffer->colorsPerLed; j++)
    {
      *gradient_spec++;
    }

    uint32_t hsv2 = grb2hsv(g2, r2, b2);
    h2 = (hsv2 & 0xFFFF0000) >> 16;
    s2 = (hsv1 & 0x0000FF00) >> 8;
    v2 = (hsv1 & 0x000000FF);

    // get distance and direction to use
    int maxCCW = h1 > h2 ? h1 - h2 : 360 + h1 - h2;
    int maxCW = h1 > h2 ? 360 + h2 - h1 : h2 - h1;

    // Fill buffer
    int numPixels = segmentSize;
    // make sure we fill the strip correctly in case of rounding errors
    if (k == segments - 1) {
      numPixels = buffer->size - (segmentSize * (segments - 1));
    }

    int steps = numPixels - 1;

    for(i = 0; i < numPixels; i++) {
      // calculate HSV values
      //h = h1 + ((h2-h1) * i / fillSize);
      int h = maxCCW > maxCW ? h1 + ((maxCW * i / steps) % 360) : h1 - (maxCCW * i / steps);
      if (h < 0) h = h + 360;
      if (h > 359) h = h - 360;
      s = s1 + ((s2-s1) * i / steps);
      v = v1 + ((v2-v1) * i / steps);
      // convert to RGB
      uint32_t grb = hsv2grb(h, s, v);

      *p++ = ((grb & 0x00FF0000) >> 16) * state->brightness / 255;
      *p++ = ((grb & 0x0000FF00) >> 8)  * state->brightness / 255;
      *p++ = (grb & 0x000000FF) * state->brightness / 255;

      for (j = 3; j < buffer->colorsPerLed; j++) {
        *p++ = 0;
      }
    }
  }

  return 0;
}