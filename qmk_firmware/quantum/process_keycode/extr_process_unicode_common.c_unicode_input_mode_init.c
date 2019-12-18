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
typedef  size_t uint8_t ;
struct TYPE_2__ {scalar_t__ input_mode; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_UNICODEMODE ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ ) ; 
 scalar_t__* selected ; 
 size_t selected_count ; 
 size_t selected_index ; 
 TYPE_1__ unicode_config ; 

void unicode_input_mode_init(void) {
    unicode_config.raw = eeprom_read_byte(EECONFIG_UNICODEMODE);
#if UNICODE_SELECTED_MODES != -1
#    if UNICODE_CYCLE_PERSIST
    // Find input_mode in selected modes
    uint8_t i;
    for (i = 0; i < selected_count; i++) {
        if (selected[i] == unicode_config.input_mode) {
            selected_index = i;
            break;
        }
    }
    if (i == selected_count) {
        // Not found: input_mode isn't selected, change to one that is
        unicode_config.input_mode = selected[selected_index = 0];
    }
#    else
    // Always change to the first selected input mode
    unicode_config.input_mode = selected[selected_index = 0];
#    endif
#endif
    dprintf("Unicode input mode init to: %u\n", unicode_config.input_mode);
}