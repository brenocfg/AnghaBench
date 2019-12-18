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
 int /*<<< orphan*/  RYS_STOKEN1 ; 
 int /*<<< orphan*/  RYS_STOKEN2 ; 
 int /*<<< orphan*/  RYS_STOKEN3 ; 
 int /*<<< orphan*/  RYS_STOKEN4 ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
#define  STOKEN1 131 
#define  STOKEN2 130 
#define  STOKEN3 129 
#define  STOKEN4 128 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case STOKEN1:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN1);
      }
      break;
    case STOKEN2:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN2);
      }
      break;
    case STOKEN3:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN3);
      }
      break;
    case STOKEN4:
      if (record->event.pressed) {
        SEND_STRING(RYS_STOKEN4);
      }
      break;
  }
  return true;
}