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
typedef  int uint32_t ;
struct TYPE_2__ {int* color; } ;

/* Variables and functions */
 TYPE_1__* state ; 
 int /*<<< orphan*/  ws2812_effects_fill_buffer (int) ; 

__attribute__((used)) static int ws2812_effects_fill_color() {

  uint8_t g = state->color[0];
  uint8_t r = state->color[1];
  uint8_t b = state->color[2];
  uint8_t w = state->color[3];

  uint32_t color = (w << 24) | (g << 16) | (r << 8) | b;

  ws2812_effects_fill_buffer(color);

  return 0;
}