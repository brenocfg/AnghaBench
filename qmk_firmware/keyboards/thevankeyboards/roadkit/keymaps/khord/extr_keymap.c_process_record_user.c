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
#define  ADMIN 131 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  SMSPC1 130 
#define  STR192 129 
#define  STR255 128 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADMIN:
      if (record->event.pressed) {
  SEND_STRING("Administrator");
      }
      return false;
      break;
    case SMSPC1:
      if (record->event.pressed) {
  SEND_STRING("Simspace1!");
      }
      return false;
      break;
    case STR192:
      if (record->event.pressed) {
  SEND_STRING("192.168.");
      }
      return false;
      break;
    case STR255:
      if (record->event.pressed) {
  SEND_STRING("255");
      }
      return false;
      break;
  }
  return true;
}