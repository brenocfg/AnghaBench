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
#define  KC_EML 128 
 int /*<<< orphan*/  PSTR (char*) ; 
 int /*<<< orphan*/  send_string_with_delay_P (int /*<<< orphan*/ ,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_EML: //use "KC_EML" as keycode in layers above to call macro
    if (!record->event.pressed) {
      send_string_with_delay_P(PSTR("example@email.com"), 10); //change email value here
    }
  break;
  }
  return true;
}