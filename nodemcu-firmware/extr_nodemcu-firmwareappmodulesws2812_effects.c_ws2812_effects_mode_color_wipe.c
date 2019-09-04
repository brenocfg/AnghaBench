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
struct TYPE_3__ {int size; int colorsPerLed; void** values; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  void* uint8_t ;
struct TYPE_4__ {int counter_mode_step; int* color; int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_mode_color_wipe() {

  ws2812_buffer * buffer = state->buffer;

  int led_index = (state->counter_mode_step % buffer->size) * buffer->colorsPerLed;

  if (state->counter_mode_step >= buffer->size)
  {
    buffer->values[led_index] = 0;
    buffer->values[led_index + 1] = 0;
    buffer->values[led_index + 2] = 0;
  }
  else
  {
    uint8_t px_r = state->color[1] * state->brightness / 255;
    uint8_t px_g = state->color[0] * state->brightness / 255;
    uint8_t px_b = state->color[2] * state->brightness / 255;
    buffer->values[led_index] = px_g;
    buffer->values[led_index + 1] = px_r;
    buffer->values[led_index + 2] = px_b;
  }
  state->counter_mode_step = (state->counter_mode_step + 1) % (buffer->size * 2);
}