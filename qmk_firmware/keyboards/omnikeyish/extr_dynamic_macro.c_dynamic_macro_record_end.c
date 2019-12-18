#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  checksum; TYPE_2__* events; } ;
typedef  TYPE_3__ dynamic_macro_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,size_t,...) ; 
 int /*<<< orphan*/  dprintln (char*) ; 
 int /*<<< orphan*/  dynamic_macro_calc_crc (TYPE_3__*) ; 
 int /*<<< orphan*/  dynamic_macro_led_blink () ; 
 int /*<<< orphan*/  dynamic_macro_save_eeprom (size_t) ; 
 TYPE_3__* dynamic_macros ; 

void dynamic_macro_record_end(uint8_t macro_id) {
  dynamic_macro_led_blink();

  dynamic_macro_t* macro  = &dynamic_macros[macro_id];
  uint8_t          length = macro->length;

  keyrecord_t* events_begin   = &(macro->events[0]);
  keyrecord_t* events_pointer = &(macro->events[length - 1]);

  dprintf("dynamic_macro: macro length before trimming: %d\n", macro->length);
  while (events_pointer != events_begin && (events_pointer)->event.pressed) {
    dprintln("dynamic macro: trimming a trailing key-down event");
    --(macro->length);
    --events_pointer;
  }

#ifdef DYNAMIC_MACRO_EEPROM_STORAGE
  macro->checksum = dynamic_macro_calc_crc(macro);
  dynamic_macro_save_eeprom(macro_id);
#endif

  dprintf("dynamic macro: slot %d saved, length: %d\n", macro_id, length);
}