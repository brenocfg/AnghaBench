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
#define  CHIKA 140 
#define  DIA 139 
 int /*<<< orphan*/  IS_LAYER_ON (int /*<<< orphan*/ ) ; 
#define  KANAN 138 
 int /*<<< orphan*/  LED_default_set () ; 
 int /*<<< orphan*/  LED_layer_set (int) ; 
#define  MARI 137 
#define  RETURN_SCHOOL_IDOL_FESTIVAL 136 
#define  RIKO 135 
#define  RUBY 134 
#define  RUBY_SUB1 133 
#define  RUBY_SUB2 132 
 int /*<<< orphan*/  SEND_CHIKA ; 
 int /*<<< orphan*/  SEND_DIA ; 
 int /*<<< orphan*/  SEND_KANAN ; 
 int /*<<< orphan*/  SEND_MARI ; 
 int /*<<< orphan*/  SEND_RIKO ; 
 int /*<<< orphan*/  SEND_RUBY ; 
 int /*<<< orphan*/  SEND_YOHANE ; 
 int /*<<< orphan*/  SEND_YOU ; 
 int /*<<< orphan*/  SEND_ZURA ; 
#define  TO_SCHOOL_IDOL_FESTIVAL 131 
#define  YOHANE 130 
#define  YOU 129 
#define  ZURA 128 
 int /*<<< orphan*/  _CHIKA ; 
 int /*<<< orphan*/  _DIA ; 
 int /*<<< orphan*/  _KANAN ; 
 int /*<<< orphan*/  _MARI ; 
 int /*<<< orphan*/  _RIKO ; 
 int /*<<< orphan*/  _RUBY ; 
 int /*<<< orphan*/  _RUBY_SUB1 ; 
 int /*<<< orphan*/  _RUBY_SUB2 ; 
 int /*<<< orphan*/  _RUBY_SUB3 ; 
 int /*<<< orphan*/  _SCHOOL_IDOL_FESTIVAL ; 
 int /*<<< orphan*/  _YOHANE ; 
 int /*<<< orphan*/  _YOU ; 
 int /*<<< orphan*/  _ZURA ; 
 int /*<<< orphan*/  check_tap_and_send_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int long_tap_timer ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case DIA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_DIA);
        LED_layer_set(3);
      } else {
        check_tap_and_send_key(SEND_DIA);
        layer_off(_DIA);
        LED_default_set();
      }
      break;

    case YOU:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOU);
        LED_layer_set(4);
      } else {
        check_tap_and_send_key(SEND_YOU);
        layer_off(_YOU);
        LED_default_set();
      }
      break;

    case CHIKA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_CHIKA);
        LED_layer_set(0);
      } else {
        check_tap_and_send_key(SEND_CHIKA);
        layer_off(_CHIKA);
        LED_default_set();
      }
      break;

    case ZURA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_ZURA);
        LED_layer_set(6);
      } else {
        check_tap_and_send_key(SEND_ZURA);
        layer_off(_ZURA);
        LED_default_set();
      }
      break;

    case RUBY:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RUBY);
        LED_layer_set(8);
      } else {
        check_tap_and_send_key(SEND_RUBY);
        layer_off(_RUBY);
        LED_default_set();
      }
      break;
    case RUBY_SUB1:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB1);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB1);
      }
      break;
    case RUBY_SUB2:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB2);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB2);
      }
      break;

    case YOHANE:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOHANE);
        LED_layer_set(5);
      } else {
        check_tap_and_send_key(SEND_YOHANE);
        layer_off(_YOHANE);
        LED_default_set();
      }
      break;

    case RIKO:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RIKO);
        LED_layer_set(1);
      } else {
        check_tap_and_send_key(SEND_RIKO);
        layer_off(_RIKO);
        LED_default_set();
      }
      break;

    case MARI:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_MARI);
        LED_layer_set(7);
      } else {
        check_tap_and_send_key(SEND_MARI);
        layer_off(_MARI);
        LED_default_set();
      }
      break;

    case KANAN:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_KANAN);
        LED_layer_set(2);
      } else {
        check_tap_and_send_key(SEND_KANAN);
        layer_off(_KANAN);
        LED_default_set();
      }
      break;

    case TO_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        LED_default_set();
        layer_on(_SCHOOL_IDOL_FESTIVAL);
      }
      break;
    case RETURN_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        layer_off(_SCHOOL_IDOL_FESTIVAL);
      }
      break;
  }

  return true;
}