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
struct TYPE_3__ {int* values; int size; int colorsPerLed; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int counter_mode_step; int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 int color_wheel (int) ; 
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_mode_rainbow() {

  ws2812_buffer * buffer = state->buffer;

  uint32_t color = color_wheel(state->counter_mode_step);
  uint8_t r = (color & 0x00FF0000) >> 16;
  uint8_t g = (color & 0x0000FF00) >>  8;
  uint8_t b = (color & 0x000000FF) >>  0;

  // Fill buffer
  int i,j;
  uint8_t * p = &buffer->values[0];
  for(i = 0; i < buffer->size; i++) {
    *p++ = g * state->brightness / 255;
    *p++ = r * state->brightness / 255;
    *p++ = b * state->brightness / 255;
    for (j = 3; j < buffer->colorsPerLed; j++)
    {
      *p++ = 0;
    }
  }

  state->counter_mode_step = (state->counter_mode_step + 1) % 360;
  return 0;
}