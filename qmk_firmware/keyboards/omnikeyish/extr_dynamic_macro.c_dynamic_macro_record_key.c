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
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_8__ {size_t length; TYPE_2__* events; } ;
typedef  TYPE_3__ dynamic_macro_t ;

/* Variables and functions */
 size_t DYNAMIC_MACRO_SIZE ; 
 int /*<<< orphan*/  dprintf (char*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  dprintln (char*) ; 
 int /*<<< orphan*/  dynamic_macro_led_blink () ; 
 TYPE_3__* dynamic_macros ; 

void dynamic_macro_record_key(uint8_t macro_id, keyrecord_t* record) {
  dynamic_macro_t* macro  = &dynamic_macros[macro_id];
  uint8_t          length = macro->length;

  /* If we've just started recording, ignore all the key releases. */
  if (!record->event.pressed && length == 0) {
    dprintln("dynamic macro: ignoring a leading key-up event");
    return;
  }

  if (length < DYNAMIC_MACRO_SIZE) {
    macro->events[length] = *record;
    macro->length         = ++length;
  } else {
    dynamic_macro_led_blink();
  }

  dprintf("dynamic macro: slot %d length: %d/%d\n", macro_id, length, DYNAMIC_MACRO_SIZE);
}