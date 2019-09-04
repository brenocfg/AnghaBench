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
struct TYPE_4__ {int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_gradient_rgb(const char *buffer1, size_t length1) {

  ws2812_buffer * buffer = state->buffer;

  int segments = (length1 / buffer->colorsPerLed) - 1;
  int segmentSize = buffer->size / segments;

  uint8_t g1, r1, b1, g2, r2, b2;
  int i,j,k;

  g2 = *buffer1++;
  r2 = *buffer1++;
  b2 = *buffer1++;
  // skip non-rgb components
  for (j = 3; j < buffer->colorsPerLed; j++)
  {
    *buffer1++;
  }

  // reference to buffer memory
  uint8_t * p = &buffer->values[0];
  for (k = 0; k < segments; k++) {
    g1 = g2;
    r1 = r2;
    b1 = b2;

    g2 = *buffer1++;
    r2 = *buffer1++;
    b2 = *buffer1++;

    for (j = 3; j < buffer->colorsPerLed; j++) {
      *buffer1++;
    }

    // Fill buffer
    int numPixels = segmentSize;
    // make sure we fill the strip correctly in case of rounding errors
    if (k == segments - 1) {
      numPixels = buffer->size - (segmentSize * (segments - 1));
    }

    int steps = numPixels - 1;

    for(i = 0; i < numPixels; i++) {
      *p++ = (g1 + ((g2-g1) * i / steps)) * state->brightness / 255;
      *p++ = (r1 + ((r2-r1) * i / steps)) * state->brightness / 255;
      *p++ = (b1 + ((b2-b1) * i / steps)) * state->brightness / 255;
      for (j = 3; j < buffer->colorsPerLed; j++)
      {
        *p++ = 0;
      }
    }
  }

  return 0;
}