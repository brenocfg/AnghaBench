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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int tap_tog_count ; 
 int tap_tog_layer_other_key_pressed ; 
 int tap_tog_layer_toggled_on ; 

void process_tap_tog(uint8_t layer, keyrecord_t *record) {
  tap_tog_count++;
  // press
  if (record->event.pressed) {

    // TTL has already been pressed and we are toggled into that layer
    // so now we need to leave
    if(tap_tog_layer_toggled_on) {
      layer_clear();
      tap_tog_layer_toggled_on = false;
    }

    // this means we're in our default layer
    // so switch the layer immediately
    // whether we'll switch back when it's released depends on if a button gets pressed while this is held down
    else {
      // switch layer
      layer_on(layer);
      tap_tog_layer_other_key_pressed = false; // if this becomes true before it gets released, it will act as a held modifier
    }
  }

  // release
  else {
    // if it was used as a held modifier (like traditional shift)
    if(tap_tog_layer_other_key_pressed) {
      // switch layer back
      layer_clear();
    }
    // if it was used as a toggle button
    else {
      // next time, it will turn layer off
      tap_tog_layer_toggled_on = true;

      // If it's been tapped twice, reset the toggle flag.
      // Otherwise, we get stuck oscillating between this code block and the
      // pressed && TTL_toggled_on block.
      if (tap_tog_count >= 4 ) {
        tap_tog_count = 0;
        tap_tog_layer_toggled_on = false;
      }
    }
  }
}