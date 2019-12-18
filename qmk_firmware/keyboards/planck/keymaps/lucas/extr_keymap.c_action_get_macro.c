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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE_LESS ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  switch(id) {
    case 0: // M(0)
        if (record->event.pressed) {
            register_code(KC_LSFT);
            layer_on(1);
        } else {
            layer_off(1);
            unregister_code(KC_LSFT);
        }
        break;       
    case 1: // M(1)
        if (record->event.pressed) {
            unregister_code(KC_LSFT);
            register_code(DE_LESS);
        } else {
            unregister_code(DE_LESS);
        }
        break;    
  }
  return MACRO_NONE;

}