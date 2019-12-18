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
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  LCTL ; 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  RALT ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RSFT ; 
 int /*<<< orphan*/  T (int) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checktime () ; 
 int /*<<< orphan*/  key_timer ; 
 int /*<<< orphan*/  timer_read () ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) { // MACRODOWN only works in this function
    switch(id) {
        case 0: //MAC0 - Hold for lshift and { on tap
					if (record->event.pressed) {
						key_timer = timer_read();
						return MACRO(D(LSFT), END );
					} else {
						return checktime() ? MACRO(U(LSFT),D(RALT),T(7),U(RALT),END): MACRO(U(LSFT),END);
					}; break;
			  case 1:	//MAC1 - Hold for rshift and } on tap
					if (record->event.pressed) {
						key_timer = timer_read();
						return MACRO(D(RSFT), END );
					} else {
						return checktime()  ? MACRO(U(RSFT),D(RALT),T(0),U(RALT),END): MACRO(U(RSFT),END);
					}; break;
        case 2: //MAC2 - Hold for lctrl and [ on tap
						if (record->event.pressed) {
							key_timer = timer_read();
							return MACRO(D(LCTL), END );
						} else {return checktime() ? MACRO(U(LCTL),D(RALT),T(8),U(RALT),END):MACRO(U(LCTL),END);
						}; break;
       	case 3: //MAC3 - Hold for rctrl and ] on tap
						if (record->event.pressed) {
							key_timer = timer_read();
							return MACRO(D(RCTL), END );
						} else {
							return checktime() ? MACRO(U(RCTL),D(RALT),T(9),U(RALT),END):MACRO(U(RCTL),END);
						}; break;
      	case 4: //MAC4 reserved for later.
						if (record->event.pressed) { } else { }; break;
       	case 5: //MAC5 reserved for later.
						if (record->event.pressed) { } else { }; break;
       	case 6: //MAC6 reserved for later.
						if (record->event.pressed) { } else { }; break;
    } return MACRO_NONE;
}