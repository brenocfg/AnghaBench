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
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;
struct TYPE_6__ {scalar_t__ pressed; TYPE_1__ key; } ;
struct TYPE_7__ {TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
#define  KC_BBB 129 
#define  KC_BEPIS 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  oled_on () ; 
 int /*<<< orphan*/  oled_timer ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  uprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
      uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

    if (record->event.pressed) {
      #ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read();
        oled_on();
        #endif // OLED_DRIVER_ENABLE
    switch (keycode) {
            case KC_BBB:
                if (record->event.pressed) {
                    SEND_STRING(":b:");
                } else {}
                break;
            case KC_BEPIS:
                if (record->event.pressed) {
                    SEND_STRING("BEPIS");
                } else {}
                break;
        }
    }
    return true;

}