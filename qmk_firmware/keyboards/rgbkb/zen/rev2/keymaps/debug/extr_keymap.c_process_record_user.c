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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int col; int row; } ;
struct TYPE_5__ {TYPE_2__ key; scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_string (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static char buf[10] = " ";

    if (record->event.pressed) {
      snprintf(buf, 10, "C%dR%d ", record->event.key.col, record->event.key.row);

      send_string(buf);
    }
    return false;

  return true;
}