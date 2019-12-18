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
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_UP (int /*<<< orphan*/ ) ; 
#define  SWTCH 128 
 int /*<<< orphan*/  X_ENTER ; 
 int /*<<< orphan*/  X_LGUI ; 
 int /*<<< orphan*/  X_LSHIFT ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case SWTCH:
        SEND_STRING(SS_DOWN(X_LGUI));
        SEND_STRING(SS_DOWN(X_LSHIFT));
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING(SS_UP(X_LSHIFT));
        SEND_STRING(SS_UP(X_LGUI));
        return false;
    }
  }
  return true;
}