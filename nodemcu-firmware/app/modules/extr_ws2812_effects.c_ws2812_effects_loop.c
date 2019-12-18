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
struct TYPE_2__ {scalar_t__ effect_type; int effect_int_param1; int counter_mode_step; int mode_delay; int counter_mode_call; int running; int /*<<< orphan*/  os_t; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int EFFECT_PARAM_INVALID ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHIFT_CIRCULAR ; 
 int UINT32_MAX ; 
 scalar_t__ WS2812_EFFECT_BLINK ; 
 scalar_t__ WS2812_EFFECT_CIRCUS_COMBUSTUS ; 
 scalar_t__ WS2812_EFFECT_COLOR_WIPE ; 
 scalar_t__ WS2812_EFFECT_CYCLE ; 
 scalar_t__ WS2812_EFFECT_FIRE_FLICKER ; 
 scalar_t__ WS2812_EFFECT_FIRE_FLICKER_INTENSE ; 
 scalar_t__ WS2812_EFFECT_FIRE_FLICKER_SOFT ; 
 scalar_t__ WS2812_EFFECT_FLICKER ; 
 scalar_t__ WS2812_EFFECT_HALLOWEEN ; 
 scalar_t__ WS2812_EFFECT_LARSON_SCANNER ; 
 scalar_t__ WS2812_EFFECT_RAINBOW ; 
 scalar_t__ WS2812_EFFECT_RAINBOW_CYCLE ; 
 scalar_t__ WS2812_EFFECT_RANDOM_COLOR ; 
 scalar_t__ WS2812_EFFECT_RANDOM_DOT ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  ws2812_buffer_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ws2812_effects_mode_blink () ; 
 int /*<<< orphan*/  ws2812_effects_mode_color_wipe () ; 
 int ws2812_effects_mode_delay () ; 
 int /*<<< orphan*/  ws2812_effects_mode_flicker_int (int) ; 
 int /*<<< orphan*/  ws2812_effects_mode_larson_scanner () ; 
 int /*<<< orphan*/  ws2812_effects_mode_rainbow () ; 
 int /*<<< orphan*/  ws2812_effects_mode_random_color () ; 
 int /*<<< orphan*/  ws2812_effects_mode_random_dot (int) ; 
 int /*<<< orphan*/  ws2812_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ws2812_effects_loop(void *p)
{

  if (state->effect_type == WS2812_EFFECT_BLINK)
  {
    ws2812_effects_mode_blink();
  }
  else if (state->effect_type == WS2812_EFFECT_RAINBOW)
  {
    ws2812_effects_mode_rainbow();
  }
  else if (state->effect_type == WS2812_EFFECT_RAINBOW_CYCLE)
  {
    // the rainbow cycle effect can be achieved by shifting the buffer
    ws2812_buffer_shift(state->buffer, 1, SHIFT_CIRCULAR, 1, -1);
  }
  else if (state->effect_type == WS2812_EFFECT_FLICKER)
  {
    int flicker_value = state->effect_int_param1 != EFFECT_PARAM_INVALID ? state->effect_int_param1 : 100;
    if (flicker_value == 0) {
      flicker_value = 50;
    }
    ws2812_effects_mode_flicker_int(flicker_value);
    state->counter_mode_step = (state->counter_mode_step + 1) % 256;
  }
  else if (state->effect_type == WS2812_EFFECT_FIRE_FLICKER)
  {
    ws2812_effects_mode_flicker_int(110);
    state->counter_mode_step = (state->counter_mode_step + 1) % 256;
  }
  else if (state->effect_type == WS2812_EFFECT_FIRE_FLICKER_SOFT)
  {
    ws2812_effects_mode_flicker_int(70);
    state->counter_mode_step = (state->counter_mode_step + 1) % 256;
  }
  else if (state->effect_type == WS2812_EFFECT_FIRE_FLICKER_INTENSE)
  {
    ws2812_effects_mode_flicker_int(170);
    state->counter_mode_step = (state->counter_mode_step + 1) % 256;
  }
  else if (state->effect_type == WS2812_EFFECT_RANDOM_COLOR)
  {
    ws2812_effects_mode_random_color();
  }
  else if (state->effect_type == WS2812_EFFECT_HALLOWEEN)
  {
    ws2812_buffer_shift(state->buffer, 1, SHIFT_CIRCULAR, 1, -1);
  }
  else if (state->effect_type == WS2812_EFFECT_CIRCUS_COMBUSTUS)
  {
    ws2812_buffer_shift(state->buffer, 1, SHIFT_CIRCULAR, 1, -1);
  }
  else if (state->effect_type == WS2812_EFFECT_LARSON_SCANNER)
  {
    ws2812_effects_mode_larson_scanner();
  }
  else if (state->effect_type == WS2812_EFFECT_CYCLE)
  {
    ws2812_buffer_shift(state->buffer, state->effect_int_param1, SHIFT_CIRCULAR, 1, -1);
  }
  else if (state->effect_type == WS2812_EFFECT_COLOR_WIPE)
  {
    ws2812_effects_mode_color_wipe();
  }
  else if (state->effect_type == WS2812_EFFECT_RANDOM_DOT)
  {
    uint8_t dots = state->effect_int_param1 != EFFECT_PARAM_INVALID ? state->effect_int_param1 : 1;
    ws2812_effects_mode_random_dot(dots);
  }

  // set the new delay for this effect
  state->mode_delay = ws2812_effects_mode_delay();
  // call count
  state->counter_mode_call = (state->counter_mode_call + 1) % UINT32_MAX;
  // write the buffer
  ws2812_write(state->buffer);
  // set the timer
  if (state->running == 1 && state->mode_delay >= 10)
  {
    os_timer_disarm(&(state->os_t));
    os_timer_arm(&(state->os_t), state->mode_delay, FALSE);
  }
}