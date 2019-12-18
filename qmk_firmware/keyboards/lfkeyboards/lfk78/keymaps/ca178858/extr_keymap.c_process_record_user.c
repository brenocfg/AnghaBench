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
 int CS_GO ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int layer_state ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if((layer_state & (1 << CS_GO)) && (keycode == 44)){
    if(get_mods() & (MOD_BIT(KC_LGUI))){
      return false;
    }
  }
  return true;
}