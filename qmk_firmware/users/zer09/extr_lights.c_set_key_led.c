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
typedef  int uint8_t ;
struct TYPE_5__ {int row; int col; } ;
struct TYPE_6__ {scalar_t__ pressed; TYPE_1__ key; } ;
struct TYPE_7__ {TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_LED_RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** _LC ; 
 int /*<<< orphan*/ * _PC ; 
 int* active_key_pos ; 
 int /*<<< orphan*/  led_dim ; 

void set_key_led(keyrecord_t *record, uint8_t lyr) {
  static uint8_t base = 5;

  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  uint8_t pos;

  // This was the result of my soldering.
  // Lesson of the day: always check.
  if (r < 5) {
    pos = r % 2 == 0 ? r * base + c : r * base + (base - (c + 1));
  } else {
    pos = r % 2 == 0 ? r * base + (base - (c + 1)) : r * base + c;
  }

  if (record->event.pressed) {
    active_key_pos[pos] = true;
    SET_LED_RGB(_PC[0], _PC[1], _PC[2], led_dim, pos);
  } else {
    active_key_pos[pos] = false;
    SET_LED_RGB(_LC[lyr][0], _LC[lyr][1], _LC[lyr][2], led_dim, pos);
  }
}