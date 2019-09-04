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
struct TYPE_3__ {int size; int colorsPerLed; int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ ws2812_buffer ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int brightness; TYPE_1__* buffer; } ;

/* Variables and functions */
 TYPE_2__* state ; 

__attribute__((used)) static int ws2812_effects_mode_circus_combustus() {
  ws2812_buffer * buffer = state->buffer;

  int g1 = 0 * state->brightness / 255;
  int r1 = 255 * state->brightness / 255;
  int b1 = 0 * state->brightness / 255;

  int g2 = 255 * state->brightness / 255;
  int r2 = 255 * state->brightness / 255;
  int b2 = 255 * state->brightness / 255;

  // Fill buffer
  int i,j;
  uint8_t * p = &buffer->values[0];
  for(i = 0; i < buffer->size; i++) {
    if (i % 6 < 2) {
      *p++ = g1;
      *p++ = r1;
      *p++ = b1;
    }
    else if (i % 6 < 4) {
      *p++ = g2;
      *p++ = r2;
      *p++ = b2;
    }
    else {
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
    }
    for (j = 3; j < buffer->colorsPerLed; j++)
    {
      *p++ = 0;
    }
  }

  return 0;
}