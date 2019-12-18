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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ speed; scalar_t__ mode_delay; int effect_type; } ;

/* Variables and functions */
 int SPEED_MAX ; 
#define  WS2812_EFFECT_BLINK 141 
#define  WS2812_EFFECT_CIRCUS_COMBUSTUS 140 
#define  WS2812_EFFECT_COLOR_WIPE 139 
#define  WS2812_EFFECT_CYCLE 138 
#define  WS2812_EFFECT_FIRE_FLICKER 137 
#define  WS2812_EFFECT_FIRE_FLICKER_INTENSE 136 
#define  WS2812_EFFECT_FIRE_FLICKER_SOFT 135 
#define  WS2812_EFFECT_FLICKER 134 
#define  WS2812_EFFECT_HALLOWEEN 133 
#define  WS2812_EFFECT_LARSON_SCANNER 132 
#define  WS2812_EFFECT_RAINBOW 131 
#define  WS2812_EFFECT_RAINBOW_CYCLE 130 
#define  WS2812_EFFECT_RANDOM_COLOR 129 
#define  WS2812_EFFECT_RANDOM_DOT 128 
 int rand () ; 
 TYPE_1__* state ; 

__attribute__((used)) static uint32_t ws2812_effects_mode_delay()
{
  // check if delay has been set explicitly
  if (state->speed == 0 && state->mode_delay > 0)
  {
    return state->mode_delay;
  }

  uint32_t delay = 10;
  switch (state->effect_type) {
    case WS2812_EFFECT_BLINK:
    case WS2812_EFFECT_RAINBOW:
    case WS2812_EFFECT_RAINBOW_CYCLE:
      delay = 10 + ((1000 * (uint32_t)(SPEED_MAX - state->speed)) / SPEED_MAX);
    break;
    case WS2812_EFFECT_FLICKER:
    case WS2812_EFFECT_FIRE_FLICKER:
    case WS2812_EFFECT_FIRE_FLICKER_SOFT:
    case WS2812_EFFECT_FIRE_FLICKER_INTENSE:
      delay = 30 + (rand() % 100) + (200 * (SPEED_MAX - state->speed) / SPEED_MAX);
    break;

    case WS2812_EFFECT_RANDOM_COLOR:
    case WS2812_EFFECT_HALLOWEEN:
    case WS2812_EFFECT_CIRCUS_COMBUSTUS:
    case WS2812_EFFECT_LARSON_SCANNER:
    case WS2812_EFFECT_CYCLE:
    case WS2812_EFFECT_COLOR_WIPE:
    case WS2812_EFFECT_RANDOM_DOT:
      delay = 10 + ((1000 * (uint32_t)(SPEED_MAX - state->speed)) / SPEED_MAX);
    break;

  }
  return delay;
}