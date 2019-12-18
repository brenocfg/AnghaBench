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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_CAPS ; 
 int /*<<< orphan*/  KC_ENT ; 
 int /*<<< orphan*/  KC_LEFT ; 
#define  SC_INCL 132 
#define  SC_PULL 131 
#define  SC_PUSH 130 
#define  SC_SCAP 129 
#define  SC_SCOF 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  _CAPS ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    /* include some kind of library or header */
    case SC_INCL:
      if (record->event.pressed) {
        SEND_STRING("#include <>");
        tap_code(KC_LEFT);
      }
      return false;
    case SC_PULL:
      if (record->event.pressed) {
        SEND_STRING("git pull");
        tap_code(KC_ENT);
      }
      return false;
    case SC_PUSH:
      if (record->event.pressed) {
        SEND_STRING("git push");
        tap_code(KC_ENT);
      }
      return false;
    case SC_SCAP:
      if (record->event.pressed) {
        layer_on(_CAPS);
        tap_code(KC_CAPS);
      }
      return false;
    case SC_SCOF:
      if (record->event.pressed) {
        layer_off(_CAPS);
        tap_code(KC_CAPS);
      }
      return false;
    default:
      return true;
  }
  return true;
}