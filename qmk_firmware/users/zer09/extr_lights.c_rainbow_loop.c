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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {size_t pos; int status; int /*<<< orphan*/  forced; } ;

/* Variables and functions */
 int DEFAULT ; 
#define  DISABLED 129 
#define  ENABLED 128 
 size_t RBW ; 
 int /*<<< orphan*/  SET_LED_RGB (size_t,size_t,size_t,int /*<<< orphan*/ ,size_t) ; 
 size_t** _LC ; 
 size_t* _LIGHTS ; 
 int /*<<< orphan*/ * active_key_pos ; 
 int /*<<< orphan*/  led_dim ; 
 TYPE_1__* rbw_led_keys ; 
 int timer_elapsed (int) ; 
 int timer_read () ; 

bool rainbow_loop(uint8_t lyr) {
  static uint16_t last_timer = 0;
  static uint16_t i = 0;
  static uint8_t r, g, b, pos;

  if (timer_elapsed(last_timer) < 8) {
    return false;
  }

  if (i >= 360) {
    i = 0;
  }

  last_timer = timer_read();
  r = _LIGHTS[(i + 120) % 360];
  g = _LIGHTS[i];
  b = _LIGHTS[(i + 240) % 360];

  i++;

  bool set_rbw = false;

  for (uint8_t j = 0; j < RBW; j++) {
    pos = rbw_led_keys[j].pos;

    switch (rbw_led_keys[j].status) {
    case ENABLED:
      if (!active_key_pos[pos] || rbw_led_keys[j].forced) {
        SET_LED_RGB(r, g, b, led_dim, pos);
        set_rbw = true;
      }

      break;
    case DISABLED:
      if (!active_key_pos[pos] || rbw_led_keys[j].forced) {
        SET_LED_RGB(_LC[lyr][0], _LC[lyr][1], _LC[lyr][2], led_dim, pos);
        set_rbw = true;
      }

      rbw_led_keys[j].status = DEFAULT;
      break;
    default:
      break;
    }
  }

  return set_rbw;
}