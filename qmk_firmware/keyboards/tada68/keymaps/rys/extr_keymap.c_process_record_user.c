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
#define  PSTOKEN 129 
#define  QSTOKEN 128 
 int /*<<< orphan*/  RYS_PSTOKEN ; 
 int /*<<< orphan*/  RYS_QSTOKEN ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PSTOKEN:
      if (record->event.pressed) {
        SEND_STRING(RYS_PSTOKEN);
      }
      break;
    case QSTOKEN:
      if (record->event.pressed) {
        SEND_STRING(RYS_QSTOKEN);
      }
      break;
  }
  return true;
}