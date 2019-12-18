#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {scalar_t__ checksum; scalar_t__ length; } ;
typedef  TYPE_1__ dynamic_macro_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,size_t) ; 
 scalar_t__ dynamic_macro_calc_crc (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_macro_eeprom_macro_addr (size_t) ; 
 TYPE_1__* dynamic_macros ; 
 int /*<<< orphan*/  eeprom_read_block (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void dynamic_macro_load_eeprom(uint8_t macro_id) {
  dynamic_macro_t* dst = &dynamic_macros[macro_id];

  eeprom_read_block(dst, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));

  /* Validate checksum, ifchecksum is NOT valid for macro, set its length to 0 to prevent its use. */
  if (dynamic_macro_calc_crc(dst) != dst->checksum) {
    dprintf("dynamic macro: slot %d not loaded, checksum mismatch\n", macro_id);
    dst->length = 0;

    return;
  }

  dprintf("dynamic macro: slot %d loaded from eeprom, checksum okay\n", macro_id);
}