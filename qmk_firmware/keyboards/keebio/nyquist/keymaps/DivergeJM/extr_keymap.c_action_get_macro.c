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
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  R_PIPE 129 
#define  R_POINT 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
      //R Pointer: <-
        case R_POINT:
            if (record->event.pressed) { // Pointer <-
                SEND_STRING("<- ");
//                return MACRO(D(LSFT), T(COMM), U(LSFT), T(MINS), END);

            }
            break;
      //dplyr pipe: %>%
        case R_PIPE:
            if (record->event.pressed) { // dplyr pipe %>%
                SEND_STRING("%>% ");
//                return MACRO(D(LSFT), T(5), T(DOT), T(5), U(LSFT), END);
            }
            break;
    }
    return MACRO_NONE;
}