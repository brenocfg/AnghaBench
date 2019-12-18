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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {size_t col; size_t row; } ;
struct TYPE_6__ {scalar_t__ pressed; TYPE_1__ key; } ;
struct TYPE_7__ {TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int MAX_SWITCH_NAME_LENGTH ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  send_string (char*) ; 
 int /*<<< orphan*/  switch_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** switches ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t col = record->event.key.col;
  uint8_t row = record->event.key.row;

  if (record->event.pressed) {
    char name[MAX_SWITCH_NAME_LENGTH];
    switch_name(switches[row][col], name);
    send_string(name);
    SEND_STRING("\n");
  }
  return false;
}