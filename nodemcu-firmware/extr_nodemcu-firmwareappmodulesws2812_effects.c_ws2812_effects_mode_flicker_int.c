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
struct TYPE_4__ {int* color; int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 int rand () ; 
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_mode_flicker_int(uint8_t max_flicker) {

  ws2812_buffer * buffer = state->buffer;

  uint8_t p_g = state->color[0];
  uint8_t p_r = state->color[1];
  uint8_t p_b = state->color[2];

  // Fill buffer
  int i,j;
  uint8_t * p = &buffer->values[0];
  for(i = 0; i < buffer->size; i++) {
    int flicker = rand() % (max_flicker > 0 ? max_flicker : 1);
    int r1 = p_r-flicker;
    int g1 = p_g-flicker;
    int b1 = p_b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    *p++ = g1 * state->brightness / 255;
    *p++ = r1 * state->brightness / 255;
    *p++ = b1 * state->brightness / 255;
    for (j = 3; j < buffer->colorsPerLed; j++) {
      *p++ = 0;
    }
  }

  return 0;
}