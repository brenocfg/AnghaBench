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
struct TYPE_3__ {void** values; int size; int colorsPerLed; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int brightness; int /*<<< orphan*/  mode_color_index; TYPE_1__* buffer; } ;

/* Variables and functions */
 int color_wheel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_wheel_index (int /*<<< orphan*/ ) ; 
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_mode_random_color() {
  state->mode_color_index = get_random_wheel_index(state->mode_color_index);
  ws2812_buffer * buffer = state->buffer;

  uint32_t color = color_wheel(state->mode_color_index);
  uint8_t r = ((color & 0x00FF0000) >> 16) * state->brightness / 255;
  uint8_t g = ((color & 0x0000FF00) >>  8) * state->brightness / 255;
  uint8_t b = ((color & 0x000000FF) >>  0) * state->brightness / 255;

  // Fill buffer
  int i,j;
  uint8_t * p = &buffer->values[0];
  for(i = 0; i < buffer->size; i++) {
    *p++ = g;
    *p++ = r;
    *p++ = b;
    for (j = 3; j < buffer->colorsPerLed; j++)
    {
      *p++ = 0;
    }
  }
}