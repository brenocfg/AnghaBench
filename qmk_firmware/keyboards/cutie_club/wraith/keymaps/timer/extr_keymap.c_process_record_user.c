#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAYER_SWITCH ; 
 int /*<<< orphan*/  LAYER_TIMEOUT ; 
#define  TIME_TOGGLE 128 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_time_remaining ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TIME_TOGGLE:
			// get the time when time toggle pressed
			layer_time_remaining = LAYER_TIMEOUT;
			// set the layer
			layer_on(LAYER_SWITCH);
    break;
  }
  return true;
}