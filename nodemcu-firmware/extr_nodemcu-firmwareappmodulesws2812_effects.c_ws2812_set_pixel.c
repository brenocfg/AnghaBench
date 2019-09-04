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
struct TYPE_3__ {int colorsPerLed; void** values; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* buffer; } ;

/* Variables and functions */
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_set_pixel(int pixel, uint32_t color) {
  ws2812_buffer * buffer = state->buffer;
  uint8_t g = ((color & 0x00FF0000) >> 16);
  uint8_t r = ((color & 0x0000FF00) >> 8);
  uint8_t b = (color & 0x000000FF);
  uint8_t w = buffer->colorsPerLed  == 4 ? ((color & 0xFF000000) >> 24) : 0;

  int offset = pixel * buffer->colorsPerLed;
  buffer->values[offset] = g;
  buffer->values[offset+1] = r;
  buffer->values[offset+2] = b;
  if (buffer->colorsPerLed == 4) {
    buffer->values[offset+3] = w;
  }

  return 0;
}