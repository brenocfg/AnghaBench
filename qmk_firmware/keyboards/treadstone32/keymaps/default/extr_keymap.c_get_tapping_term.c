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

/* Variables and functions */
#define  KC_BSLO 129 
#define  KC_SPRA 128 
 int TAPPING_LAYER_TERM ; 
 int TAPPING_TERM ; 

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case KC_BSLO:
      return TAPPING_LAYER_TERM;
    case KC_SPRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}