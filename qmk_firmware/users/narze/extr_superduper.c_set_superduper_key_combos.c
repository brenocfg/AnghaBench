#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 size_t CB_SUPERDUPER ; 
 int /*<<< orphan*/  EECONFIG_SUPERDUPER_INDEX ; 
#define  _COLEMAK 130 
#define  _QWERTY 129 
#define  _QWOC 128 
 int eeprom_read_byte (int /*<<< orphan*/ ) ; 
 TYPE_1__* key_combos ; 
 int /*<<< orphan*/ * superduper_combos ; 

void set_superduper_key_combos(void) {
    uint8_t layer = eeprom_read_byte(EECONFIG_SUPERDUPER_INDEX);

    switch (layer) {
        case _QWERTY:
        case _COLEMAK:
        case _QWOC:
            key_combos[CB_SUPERDUPER].keys = superduper_combos[layer];
            break;
    }
}