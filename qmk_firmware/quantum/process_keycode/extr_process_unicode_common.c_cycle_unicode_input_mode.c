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
struct TYPE_2__ {int /*<<< orphan*/  input_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persist_unicode_input_mode () ; 
 int /*<<< orphan*/ * selected ; 
 size_t selected_count ; 
 size_t selected_index ; 
 TYPE_1__ unicode_config ; 

void cycle_unicode_input_mode(uint8_t offset) {
#if UNICODE_SELECTED_MODES != -1
    selected_index            = (selected_index + offset) % selected_count;
    unicode_config.input_mode = selected[selected_index];
#    if UNICODE_CYCLE_PERSIST
    persist_unicode_input_mode();
#    endif
    dprintf("Unicode input mode cycle to: %u\n", unicode_config.input_mode);
#endif
}