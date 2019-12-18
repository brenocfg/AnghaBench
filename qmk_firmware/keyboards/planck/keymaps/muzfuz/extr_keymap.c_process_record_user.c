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
#define  BACKLIT 131 
#define  CLNEQLS 130 
#define  HASHRKT 129 
 int /*<<< orphan*/  KC_RSFT ; 
 int PORTE ; 
#define  QWERTY 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case HASHRKT:
    if (record->event.pressed)
    {
      SEND_STRING("=>");
    }
    break;
  case CLNEQLS:
    if (record->event.pressed)
    {
      SEND_STRING(":=");
    }
    break;
  case QWERTY:
    if (record->event.pressed)
    {
      print("mode just switched to qwerty and this is a huge string\n");
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  case BACKLIT:
    if (record->event.pressed)
    {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
      PORTE &= ~(1 << 6);
#endif
    }
    else
    {
      unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
      PORTE |= (1 << 6);
#endif
    }
    return false;
    break;
  }
  return true;
}