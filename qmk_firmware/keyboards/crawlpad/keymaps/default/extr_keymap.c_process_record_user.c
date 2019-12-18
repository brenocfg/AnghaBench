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
#define  BL1 131 
#define  BL2 130 
#define  BL3 129 
#define  BL4 128 
 int PORTB ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BL1:
    if (record->event.pressed) {
      PORTB |= (1 << 4);
    } else {
      PORTB &= ~(1 << 4);
    }
    return false;
  case BL2:
    if (record->event.pressed) {
      PORTB |= (1 << 5);
    } else {
      PORTB &= ~(1 << 5);
    }
    return false;
  case BL3:
    if (record->event.pressed) {
      PORTB |= (1 << 6);
    } else {
      PORTB &= ~(1 << 6);
    }
    return false;
  case BL4:
    if (record->event.pressed) {
      PORTB |= (1 << 7);
    } else {
      PORTB &= ~(1 << 7);
    }
    return false;
  }
  return true;
}