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
struct TYPE_3__ {int size; int colorsPerLed; int* values; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int* color; int counter_mode_step; TYPE_1__* buffer; } ;

/* Variables and functions */
 int rand () ; 
 TYPE_2__* state ; 
 int /*<<< orphan*/  ws2812_set_pixel (int,int) ; 

__attribute__((used)) static int ws2812_effects_mode_random_dot(uint8_t dots) {

  ws2812_buffer * buffer = state->buffer;

  // fade out
  for(int i=0; i < buffer->size * buffer->colorsPerLed; i++) {
    buffer->values[i] = buffer->values[i] >> 1;
  }

  for(int i=0; i < dots; i++) {
    // pick random pixel
    int led_index  = rand() % buffer->size;

    uint32_t color = (state->color[0] << 16) | (state->color[1] << 8) | state->color[2];
    if (buffer->colorsPerLed == 4) {
      color = color | (state->color[3] << 24);
    }
    ws2812_set_pixel(led_index, color);
  }

  state->counter_mode_step = (state->counter_mode_step + 1) % ((buffer->size * 2) - 2);
}