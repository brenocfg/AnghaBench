#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  interrupted; } ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_2__ tap; TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LBRACKET ; 
 int /*<<< orphan*/  KC_RBRACKET ; 
#define  LALT_BRACE 129 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  MOD_LALT ; 
 int /*<<< orphan*/  MOD_LSFT ; 
 int /*<<< orphan*/  MOD_RALT ; 
#define  RALT_BRACE 128 
 int /*<<< orphan*/  add_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case LALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_LALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_LALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
    case RALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_RALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_RALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
  }
  return MACRO_NONE;
}