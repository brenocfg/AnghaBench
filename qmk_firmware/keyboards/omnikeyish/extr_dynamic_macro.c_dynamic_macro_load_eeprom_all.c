#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ DYNAMIC_MACRO_COUNT ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  dynamic_macro_header_correct () ; 
 int /*<<< orphan*/  dynamic_macro_load_eeprom (scalar_t__) ; 

void dynamic_macro_load_eeprom_all(void) {
  if (!dynamic_macro_header_correct()) {
    dprintf("dynamic_macro: eeprom header not valid, not restoring macros.\n");
    return;
  }

  for (uint8_t i = 0; i < DYNAMIC_MACRO_COUNT; ++i) {
    dynamic_macro_load_eeprom(i);
  }
}