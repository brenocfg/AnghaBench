#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 scalar_t__ layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  println (char*) ; 
 TYPE_2__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_step () ; 

void dance_toggle (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    println("Double tapped, switching layers");
    if (layer_state_is(LED)) {
      layer_off(LED);
    } else {
      layer_on(LED);
    }
  } else {
    print("Single tapped: ");
    if (layer_state_is(LED)) {
#ifdef RGBLIGHT_ENABLE
      if (!rgblight_config.enable) {
        rgblight_enable();
      }
      rgblight_step();
#endif
    } else {
      println("Base layer, sending string");
      SEND_STRING("This thing is BIG!!\n");
    }
  }
}