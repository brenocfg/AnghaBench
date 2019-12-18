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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  CLOUD9_GOTO_LINE 133 
#define  CLOUD9_GOTO_SYMBOL 132 
#define  CLOUD9_NAVIGATE 131 
#define  CLOUD9_TAB_CLOSE 130 
#define  CLOUD9_TAB_LEFT 129 
#define  CLOUD9_TAB_RIGHT 128 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_LALT (char*) ; 
 int /*<<< orphan*/  SS_LCTRL (char*) ; 
 int /*<<< orphan*/  SS_LSFT (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed) {
    switch (keycode) {
		// Cloud9 macros
		case CLOUD9_TAB_LEFT:
            SEND_STRING(SS_LCTRL("["));
            return true;
			break;
		case CLOUD9_TAB_RIGHT:
            SEND_STRING(SS_LCTRL("]"));
            return true;
			break;
		case CLOUD9_TAB_CLOSE:
            SEND_STRING(SS_LALT("w"));
            return true;
			break;
		case CLOUD9_GOTO_SYMBOL:
            SEND_STRING(SS_LSFT(SS_LCTRL("e")));
            return true;
			break;
		case CLOUD9_GOTO_LINE:
            SEND_STRING(SS_LCTRL("g"));
            return true;
			break;
		case CLOUD9_NAVIGATE:
            SEND_STRING(SS_LCTRL("e"));
            return true;
			break;
	}
  }

  return true;
}