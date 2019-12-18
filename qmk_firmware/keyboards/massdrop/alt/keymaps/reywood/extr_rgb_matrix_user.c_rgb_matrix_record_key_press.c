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
struct TYPE_7__ {int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;
struct TYPE_5__ {TYPE_3__ key; scalar_t__ pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
typedef  TYPE_3__ keypos_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_nearest_led_to_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rgb_matrix_record_key_press(keyrecord_t *record) {
  if (record->event.pressed) {
    keypos_t key = record->event.key;
    set_nearest_led_to_max(key.col, key.row);
  }
}