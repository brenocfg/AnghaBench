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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  dynamic_macro_t ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_MACRO_EEPROM_MAGIC ; 
 int /*<<< orphan*/  DYNAMIC_MACRO_EEPROM_MAGIC_ADDR ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  dynamic_macro_eeprom_macro_addr (size_t) ; 
 int /*<<< orphan*/  dynamic_macro_header_correct () ; 
 int /*<<< orphan*/ * dynamic_macros ; 
 int /*<<< orphan*/  eeprom_update_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eeprom_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dynamic_macro_save_eeprom(uint8_t macro_id) {
  if (!dynamic_macro_header_correct()) {
    eeprom_write_word(DYNAMIC_MACRO_EEPROM_MAGIC_ADDR, DYNAMIC_MACRO_EEPROM_MAGIC);
    dprintf("dynamic macro: writing magic eeprom header\n");
  }

  dynamic_macro_t* src = &dynamic_macros[macro_id];

  eeprom_update_block(src, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));
  dprintf("dynamic macro: slot %d saved to eeprom\n", macro_id);
}